// CLProjectionLib.h
#pragma once
#include <cmath>
#include <array>
#include <cassert>

namespace CL
{
    using Vec2 = std::array<double,2>;
    using Vec3 = std::array<double,3>;

    inline Vec3 add(const Vec3& a,const Vec3& b){ return {a[0]+b[0],a[1]+b[1],a[2]+b[2]}; }
    inline Vec3 sub(const Vec3& a,const Vec3& b){ return {a[0]-b[0],a[1]-b[1],a[2]-b[2]}; }
    inline Vec3 mul(const Vec3& a,double s){ return {a[0]*s,a[1]*s,a[2]*s}; }
    inline double dot(const Vec3& a,const Vec3& b){ return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]; }
    inline Vec3 cross(const Vec3& a,const Vec3& b){
        return { a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0] };
    }
    inline double length(const Vec3& v){ return std::sqrt(dot(v,v)); }
    inline Vec3 normalize(const Vec3& v){
        const double L = length(v); assert(L>0.0); return mul(v, 1.0/(L>0.0?L:1.0));
    }

    struct TangentFrame
    {
        Vec3 T; // tangent x
        Vec3 B; // tangent y
        Vec3 N; // normal (center direction), unit
    };

    // Build a stable tangent frame from unit center C (N)
    inline TangentFrame BuildFrameFromCenter(const Vec3& C)
    {
        TangentFrame F; F.N = normalize(C);
        // Choose auxiliary up not parallel to N
        Vec3 up = std::fabs(F.N[2]) < 0.9 ? Vec3{0,0,1} : Vec3{0,1,0};
        F.T = normalize(cross(up, F.N));       // T = up × N
        F.B = cross(F.N, F.T);                 // B = N × T
        return F;
    }

    // Local <-> World helpers using the tangent frame
    inline Vec3 Local2World(const TangentFrame& F, const Vec3& v)
    {
        // v.x*T + v.y*B + v.z*N
        return add(add(mul(F.T, v[0]), mul(F.B, v[1])), mul(F.N, v[2]));
    }
    inline Vec3 World2Local(const TangentFrame& F, const Vec3& p)
    {
        // inverse of orthonormal matrix: transpose
        return { dot(p, F.T), dot(p, F.B), dot(p, F.N) };
    }

    // --------- Stereographic (unit sphere) -----------
    // Reference formulas (conformal; closed-form fwd/inv).  [oai_citation:1‡Wikipedia](https://en.wikipedia.org/wiki/Stereographic_projection?utm_source=chatgpt.com)

    // Sphere->Plane: input unit vector n in WORLD coords; center frame F
    inline Vec2 StereoForward(const TangentFrame& F, const Vec3& n)
    {
        // Bring to local coords with N as "north pole"
        Vec3 nl = World2Local(F, n);
        // Project from +N pole onto tangent plane z=0
        // (X,Y) = ( x/(1 - z), y/(1 - z) )
        const double denom = 1.0 - nl[2];
        // Handle projection point (z ~ 1): goes to infinity; caller should avoid far field
        const double X = nl[0] / denom;
        const double Y = nl[1] / denom;
        return { X, Y };
    }

    // Plane->Sphere: inverse of above
    inline Vec3 StereoInverse(const TangentFrame& F, const Vec2& uv)
    {
        const double X = uv[0], Y = uv[1];
        const double s2 = X*X + Y*Y;
        const Vec3 local = { 2.0*X/(1.0+s2), 2.0*Y/(1.0+s2), ( -1.0 + s2 )/(1.0+s2) };
        return normalize(Local2World(F, local));
    }

    // --------- Lambert Azimuthal Equal-Area (unit sphere) ----------
    // Polar form: ρ = 2R sin(c/2); here R=1, so ρ = 2 sin(c/2), with true azimuth. Inverse is closed-form.  [oai_citation:2‡Eu, Mircea](https://neacsu.net/geodesy/snyder/5-azimuthal/sect_24/?utm_source=chatgpt.com)

    inline Vec2 LambertAEAFwd(const TangentFrame& F, const Vec3& n)
    {
        // Local coords: nl = (x,y,z) where z = cos(c), c = angular distance from center
        Vec3 nl = World2Local(F, n);
        nl = normalize(nl);
        const double k = std::sqrt( 2.0 / (1.0 + nl[2]) ); // k = sqrt(2/(1+cos c)) = 2 cos(c/2)
        return { k * nl[0], k * nl[1] };                  // (x',y') = k * (x,y)
    }

    inline Vec3 LambertAEAInv(const TangentFrame& F, const Vec2& uv)
    {
        const double x = uv[0], y = uv[1];
        const double r2 = x*x + y*y;
        const double z  = 1.0 - r2 * 0.5;               // z = 1 - r^2/2
        const double k  = std::sqrt(1.0 - (r2*0.25));   // k = sqrt(1 - r^2/4) = cos(c/2)
        // Recover local sphere coords: (X,Y,Z) with X = x * k, Y = y * k, Z = z
        const Vec3 local = normalize( Vec3{ x * k, y * k, z } );
        return normalize(Local2World(F, local));
    }

    // --------- Great-circle distance on unit sphere ----------
    // Robust haversine in vector form (inputs are unit vectors)
    inline double GreatCircleAngle(const Vec3& a, const Vec3& b)
    {
        // Clamp to [-1,1] to avoid NaNs
        double d = dot(normalize(a), normalize(b));
        if (d >  1.0) d = 1.0;
        if (d < -1.0) d = -1.0;
        return std::acos(d); // radians
    }

    // --------- Scaling for arbitrary sphere radius R ----------
    // For a physical radius R, multiply planar (u,v) by R and treat input/output unit vectors as above.
    // If you want a local scale S (meters per patch-unit), apply S on (u,v) consistently in both directions.
}
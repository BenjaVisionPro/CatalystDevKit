// ============================================
// Copyright © BenjaVision
// ============================================

#include "Transport/BVCEnvelopeWriter.h"

void FBVCEnvelopeWriter::WriteSingle(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Payload, uint32 MessageId, TArray<FBVCEnvelope>& Out)
{
    FBVCEnvelope Env;
    Env.ChannelId         = ChannelId;
    Env.Priority          = Priority;
    Env.Flags             = 0x01 /*Start*/ | 0x04 /*End*/;
    Env.MessageId         = MessageId;
    Env.TotalLength       = Payload.Num();
    Env.SequenceInMessage = 0;
    Env.Payload           = Payload;
    Out.Add(MoveTemp(Env));
}

void FBVCEnvelopeWriter::WriteFragmented(uint16 ChannelId, uint8 Priority, const TArray<uint8>& Payload, int32 MaxPayloadPerEnvelope, uint32 MessageId, TArray<FBVCEnvelope>& Out)
{
    const int32 Total = Payload.Num();
    const int32 MaxP  = FMath::Max(1, MaxPayloadPerEnvelope);

    int32  Offset = 0;
    uint16 Seq    = 0;

    while (Offset < Total)
    {
        const int32 Remaining = Total - Offset;
        const int32 Chunk     = FMath::Min(Remaining, MaxP);

        FBVCEnvelope Env;
        Env.ChannelId         = ChannelId;
        Env.Priority          = Priority;
        Env.MessageId         = MessageId;
        Env.TotalLength       = Total;
        Env.SequenceInMessage = Seq;

        const bool bFirst = (Offset == 0);
        const bool bLast  = (Offset + Chunk) >= Total;
        Env.Flags = (bFirst ? 0x01 : 0) | (bLast ? 0x04 : 0);

        Env.Payload.SetNumUninitialized(Chunk);
        FMemory::Memcpy(Env.Payload.GetData(), Payload.GetData() + Offset, Chunk);

        Out.Add(MoveTemp(Env));

        Offset += Chunk;
        Seq    += 1;
    }
}

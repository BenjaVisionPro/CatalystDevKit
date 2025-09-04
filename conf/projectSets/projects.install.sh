# conf/bvc/projects.install.sh
# Sourced helper. Defines: install_projects "<gitDir>"

install_projects() {

  gitDir="$1"
  : "${gitDir:?gitDir is required}"

  information_banner "Installing CatalystConnectGS"
  installProject.stone "file:${gitDir}/CatalystConnectGS/rowan/specs/CatalystConnectGS.ston" \
    --projectsHome="${gitDir}" -D

}
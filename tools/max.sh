#!/bin/bash
#SBATCH --partition=maxwell
#SBATCH --time=01:00:00                           # Maximum time requested
#SBATCH --nodes=1                                 # Number of nodes
#SBATCH --workdir   /home/jhktimm/sources/aoa_delta/workdir # directory must already exist!
#SBATCH --job-name  maXfel
#SBATCH --output    job-%x-%j-%N.out            # File to which STDOUT will be written
#SBATCH --error     job-%x-%j-%N.err            # File to which STDERR will be written
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.

/bin/hostname

pwd

cd /home/jhktimm/data_sshfs

ls

pwd

dockerrun -w /space/aoa_delta/workdir  -v /home/jhktimm/sources/aoa_delta/:/space/aoa_delta  -v /home/jhktimm/:/home/jhktimm  jhktimm/aoa  ./drun.sh




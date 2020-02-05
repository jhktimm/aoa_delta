#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-04:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue                                               # !!!!!!!!!!!!!!!
#SBATCH --job-name comp
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written
source ../setFixedParameter.sh

echo "#!/bin/bash" > ${aoaDirectory}/build/tmp
echo "cmake .." >> ${aoaDirectory}/build/tmp
echo "make -j8" >> ${aoaDirectory}/build/tmp

chmod +x ${aoaDirectory}/build/tmp

dockerrun -w /space/aoa_delta/build \
  --tmpfs /tmp \
  -v ${aoaDirectory}:/space/aoa_delta  \
  jhktimm/aoa ./tmp

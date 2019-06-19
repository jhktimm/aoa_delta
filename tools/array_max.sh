#!/bin/bash
#SBATCH --mail-type ALL                           # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user jhktimm@mail.desy.de          # Email to which notifications will be sent. It defaults to <userid@mail.desy.de> if none is set.
#SBATCH --time    0-05:00:00
#SBATCH --nodes            1
#SBATCH --partition maxwell
#SBATCH --no-requeue
#SBATCH --array 20-49                                                  # !!!!!!!!!!!!!!!
#SBATCH --job-name maXfel
#SBATCH --output    job-%x-%A-%a-%j-%N.out
#SBATCH --error     job-%x-%A-%a-%j-%N.err            # File to which STDERR will be written
export LD_PRELOAD=""
source /etc/profile.d/modules.sh
echo "SLURM_JOB_ID           $SLURM_JOB_ID"
echo "SLURM_ARRAY_JOB_ID     $SLURM_ARRAY_JOB_ID"
echo "SLURM_ARRAY_TASK_ID    $SLURM_ARRAY_TASK_ID"
echo "SLURM_ARRAY_TASK_COUNT $SLURM_ARRAY_TASK_COUNT"
echo "SLURM_ARRAY_TASK_MAX   $SLURM_ARRAY_TASK_MAX"
echo "SLURM_ARRAY_TASK_MIN   $SLURM_ARRAY_TASK_MIN"
((number=$SLURM_ARRAY_TASK_ID))

runnumber=1146                                                         # !!!!!!!!!!!!!!!
datadirectory=/beegfs/desy/user/jhktimm/                               # !!!!!!!!!!!!!!!
aoadirectory=/home/jhktimm/sources/aoa_delta/                          # !!!!!!!!!!!!!!!

postfix=maXfel_run${runnumber}_file${number}xx                         # !!!!!!!!!!!!!!!
filepath=/data/linac_test_main_run${runnumber}_file${number}??_*.raw   # !!!!!!!!!!!!!!!

# DONE run1146
# postfix=maXfel_run${runnumber}_file${number}
# filepath=/data/linac_test_main_run${runnumber}_file${number}_*.raw
# postfix=maXfel_run${runnumber}_file${number}x
# filepath=/data/linac_test_main_run${runnumber}_file${number}?_*.raw
# postfix=maXfel_run${runnumber}_file1${number}xx
# filepath=/data/linac_test_main_run${runnumber}_file1${number}??_*.raw
# postfix=maXfel_run${runnumber}_file${number}xx
# filepath=/data/linac_test_main_run${runnumber}_file${number}??_*.raw

echo "#!/bin/bash" > tmp${number}
echo "./daqanalysis ${postfix} ${filepath}" >> tmp${number}

cat tmp${number}

chmod +x tmp${number}

dockerrun -w /space/aoa_delta/workdir  -v ${aoadirectory}:/space/aoa_delta  -v ${datadirectory}:/data  jhktimm/aoa  ./tmp${number}

rm tmp${number}
#!/bin/bash
source ../setFixedParameter.sh

echo "#!/bin/bash" > ${aoaDirectory}/build/tmp
echo "cmake .." >> ${aoaDirectory}/build/tmp
echo "make -j8" >> ${aoaDirectory}/build/tmp

chmod +x ${aoaDirectory}/build/tmp

dockerrun -w /space/aoa_delta/build \
  --tmpfs /tmp \
  -v ${aoaDirectory}:/space/aoa_delta  \
  -it jhktimm/aoa ./tmp

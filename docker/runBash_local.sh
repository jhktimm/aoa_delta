docker pull jhktimm/aoa
docker run
   -v /home/jhktimm/sources/aoa_delta/:/space/aoa_delta
   -v /home/jhktimm/data_sshfs/:/data/
   -w /space/aoa_delta/build
   -it jhktimm/aoa bash
# getent passwd $USER > passwd_x
# echo "$(id -gn):*:$(id -g):$USER" > group_x
# docker run  -v /home/$USER/passwd_x:/etc/passwd \
#             -v /home/$USER/group_x:/etc/group \
#             --userns=host \
#             --net=host \
#             --security-opt no-new-privileges \
#             --privileged \
#             -u $(id -u):$(id -g) \
#             --group-add $(id -g) \
#             -it \
#             -v /home/jhktimm/sources/aoa_delta/:/space/aoa_delta \
#             -w /space/aoa_delta/workdir \
#             jhktimm/aoa bash

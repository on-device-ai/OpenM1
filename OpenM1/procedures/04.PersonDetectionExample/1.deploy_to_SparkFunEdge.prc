$0
Change directory
cd tensorflow
0
$1
Compile the binary
ubuntu1604 run "make -f tensorflow/lite/micro/tools/make/Makefile TARGET=sparkfun_edge person_detection_bin"
0
$2
Set up some dummy cryptographic keys
ubuntu1604 run "cp tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/tools/apollo3_scripts/keys_info0.py tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/tools/apollo3_scripts/keys_info.py"
0
$3
Create a signed binary
ubuntu1604 run "python3 tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/tools/apollo3_scripts/create_cust_image_blob.py --bin tensorflow/lite/micro/tools/make/gen/sparkfun_edge_cortex-m4/bin/person_detection.bin --load-address 0xC000 --magic-num 0xCB -o main_nonsecure_ota --version 0x0"
0
$4
Create a final version of the file 
ubuntu1604 run "python3 tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/tools/apollo3_scripts/create_cust_wireupdate_blob.py --load-address 0x20000 --bin main_nonsecure_ota.bin -i 6 -o main_nonsecure_wire --options 0x1"
0
$5
Waitting into a special "bootloader" state...
pause
0
$6
Flash the binary
ubuntu1604 run "python3 tensorflow/lite/micro/tools/make/downloads/AmbiqSuite-Rel2.2.0/tools/apollo3_scripts/uart_wired_update.py -b 921600 /dev/ttyS3 -r 1 -f main_nonsecure_wire.bin -i 6"
0

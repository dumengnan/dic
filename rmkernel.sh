#执行脚本时，输入参数：要删除的内核版本 如3.14.17
#!/bin/bash
if [ $# -eq 0 ]; then
	echo "argument error"
	exit 1
fi
sudo rm -rf /lib/modules/*$1*
sudo rm -rf /usr/src/*$1*
sudo rm -rf /boot/*$1*
sudo rm -rf /var/lib/dpkg/info/*$*

sudo update-grub

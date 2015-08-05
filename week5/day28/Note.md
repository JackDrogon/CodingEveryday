## Note

### Ubuntu Locale

#### 1. Debian 可以用 dpkg-reconfigure locales 来设定

#### 2. locale-gen
```
locale-gen zh_CN.UTF-8
locale-gen zh_CN
locale-gen zh_CN.GBK
locale-gen zh_CN.GB18030
```

#### 3. 修改i18n ~/.i18n, shell config file

```
LANG="zh_CN.UTF-8"
LANGUAGE="zh_CN:zh"
```
退出保存，然后执行：
locale-gen --purge
重新生成，带上--purge(用来删除所有旧的配置，在出现问题时很有用),不然在编译时可以会报错，然后重启系统即可。

#### 4. 全局配置目录

```shell
$: cat /etc/default/locale
LANG="en_US.UTF-8"
LANGUAGE="en_US:en"

$: cat /etc/environment
```

#### 5. 查看

```shell
$: locale
```

### 给虚拟机缩容(shrink)

```
VBoxManage modifyhd ----compact boot2docker-vm.vmdk
```

```shell
$ vagrant up
$ vagrant ssh
$ sudo dd if=/dev/zero of=wipefile bs=1024x1024; sync; sleep 3; sync; rm wipefile
$ exit
$ vagrant halt
$ vmware-vdiskmanager -d /path/to/main.vmdk
$ vmware-vdiskmanager -k /path/to/main.vmdk
```

格式转换
```
$ VboxManage clonehd name-of-original-vm.vdi name-of-clone-vm.vdi
```
If you want to resize the virtual disk, you should use 
```
VBoxManage modifyhd --resize <megabytes> /path/to/vdisk.vmdk.
```

### ssh反向链接，解决内外网问题

#### 1. 在被控端运行
```
ssh -f -N -R 10000:localhost:22 username@主控端ip

#这里的10000和22是端口号，也就是说，在主控端10000端口和被控端的22端口上建立了一个通道。如果主控端的ssh端口號不是默認的還要加 –p port參數

```

#### 2. 在主控端运行

```
ssh username@localhost -p 10000

#username是你被控端的username，10000就是刚才的那个端口号。 
```

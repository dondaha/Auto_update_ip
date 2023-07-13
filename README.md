# 定时更新本机IP地址到阿里云解析
定期将阿里云域名解析到本机，本地实现DDNS。A repository that implements DDNS functionality, which can periodically update the local IP address to Alibaba Cloud domain name resolution service.
## 使用方法

### 自行构建

TODO

### 从Release中下载

在右侧Release中下载 

解压后，修改`config.yaml`文件。
```yaml
Access_key:
  ## Alibaba loud access key id and secret
  access_key_id: access_key_id
  access_key_secret: access_key_secret
Domain_info:
  ## [need editing] domain record ip
  record_id: 123456789123456789
  ## [need editing] domain prefix
  rr: you_domain_prefix
  ## domain type
  type: A
Network_info:
  ## last ip address
  ip: 192.168.1.100
  ## [need editing] MAC address of the network card
  mac: 04-2A-16-6D-3D-7A 
Update_info:
  ## update interval, unit: second
  update_interval: 300 
  ## hide windows
  hide_windows: true
```

[创建AccessKey](https://help.aliyun.com/document_detail/116401.html?spm=a2c4g.28625.0.0)后，查找到域名的
`record_ip`并填入，同时填入你的域名前缀。mac地址也必须填入，否则无法获取到对应网卡的IP地址。`update_interval`为更新间隔，单位为秒。`hide_windows`为是否隐藏窗口，
如果为`true`则不会显示窗口，隐藏之后在后台运行，可以通过任务管理器关闭，任务名称和可执行文件同名。`ip`为上一次更新的IP地址，可以不用更改，如果运行
结构正确则会自动更新。

编辑好之后，运行`Auto_update_ip.exe`即可。

可以将`hide_windows`设置为`true`，然后将可执行文件放入开机启动项，这样就可以实现开机静默开始自动更新IP地址。

开机自动启动的方式目前为手动添加到注册表，自动添加到注册表[TODO]

在注册表中找到`HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run`，
新建字符串值，名称为`Auto_update_ip`，数据为可执行文件的绝对路径，如下图所示
![./.MD_images/img_1.png](img_1.png)

这样就可以实现开机自动更新IP地址了。

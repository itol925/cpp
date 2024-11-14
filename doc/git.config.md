## 设置git代理
```
# 配置socks5代理
git config --global http.proxy socks5 127.0.0.1:7890
git config --global https.proxy socks5 127.0.0.1:7890
 
# 配置http代理
git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890

```
## 查看设置
```asm
git config --global --get http.proxy
git config --global --get https.proxy
```

## 取消代理
```asm
git config --global --unset http.proxy
git config --global --unset https.proxy

```
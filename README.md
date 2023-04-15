# Hosts-File-URL-Blocker
Simple C++ Application designed to append URLs to a Windows hosts file prefixing the URLs with 127.0.0.1 &lt;entered url> to perform a local DNS block of websites

# How it Works
This application is intended to run as Administrator as it will append URLs to a hosts file

When launched a simple GUI is opened that allows you to add one or many URLs (1 URL per line) that will then add those URLs to your hosts file. For example, if you enter in google.com as the URL, when you click on Add URLs button, it will add a line to your hosts file (C:\Windows\System32\drivers\etc\hosts) 127.0.0.1 google.com

When this is done, it will block the local computer from resolving google.com as it will resolve as 127.0.0.1. Please also note that for some websites in order to successfully block the URLs will need to have google.com and www.google.com to effectively block the URL.

![HostsFileURLBlocker](https://user-images.githubusercontent.com/130707762/232176977-2392d8f2-26cb-492f-b923-5c4b9da71092.PNG)

I made this as I am a computer repair technician and have seen many systems come into our shop with the OneLaunch adware that seems to be an attack vector for scammers to deliver malicious ads to call the scammers. Almost every system that comes in with a full system compromise has had OneLaunch installed shortly before a scammer was able to convince the user to install a remote access software such as AnyDesk.

Hope you find this useful :)

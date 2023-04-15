# Hosts-File-URL-Blocker
Simple C++ Application designed to append URLs to a Windows hosts file prefixing the URLs with 127.0.0.1 &lt;entered url> to perform a local DNS block of websites

# How it Works
This application is intended to run as Administrator as it will append URLs to a hosts file. The 1.0.1 binary release should already create run as admin shortcut for the application

When launched a simple GUI is opened that allows you to add one or many URLs (1 URL per line) that will then add those URLs to your hosts file. For example, if you enter in google.com as the URL, when you click on Add URLs button, it will add a line to your hosts file (C:\Windows\System32\drivers\etc\hosts) 127.0.0.1 google.com

When this is done, it will block the local computer from resolving google.com as it will resolve as 127.0.0.1. Please also note that for some websites in order to successfully block the URLs will need to have google.com and www.google.com to effectively block the URL.

The 1.0.1 update also includes the ability to upload a URL list document for bulk domain/ip blocking. It also has a Flush DNS option that simply runs the ipconfig /flushdns command to flush the DNS resolver cache for the workstation

![HostsFileURLBlocker1 0 1](https://user-images.githubusercontent.com/130707762/232248091-c4bf0130-2be4-42b1-95fc-5e1f18a063f2.PNG)

I made this as I am a computer repair technician and have seen many systems come into our shop with the OneLaunch adware that seems to be an attack vector for scammers to deliver malicious ads to call the scammers. Almost every system that comes in with a full system compromise has had OneLaunch installed shortly before a scammer was able to convince the user to install a remote access software such as AnyDesk.

Hope you find this useful :)

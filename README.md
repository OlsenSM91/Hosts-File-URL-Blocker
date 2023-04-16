# Hosts-File-URL-Blocker
Simple C++ Application designed to append URLs to a Windows hosts file prefixing the URLs with 127.0.0.1 &lt;entered url> to perform a local DNS block of websites

# Features
I have now updated to version 1.0.2 which has several new features. There are still more features planned, but I need to stretch my legs a bit and think where I want to go with this tool. I mainly made it for work to easily block OneLaunch domains via the hosts file, but it does have some other usage cases.

- Drop down menu with pre-configured URL lists (these pull from the URL Lists folder on this repo)
- Ability to Lock/Unlock the hosts file (Changes attributes from read-only and not)
- Manually type or copy and paste to block URLs
- Import a text file of URLs to block
- Flush DNS Cache

Features to come:
- Edit hosts file/undo or remove

# How it Works
This application is intended to run as Administrator as it will append URLs to a hosts file. Since the 1.0.1 binary release, the installer will create run as admin shortcut for the application, the 1.0.2 release has a portable (no need to install) version that has property sets to run as administrator. You may need to right click the EXE to run as admin. Also please note that Antivirus may detect this application as a trojan or virus. Due to the nature of the application since it edits a Windows system file (hosts) it can and should be marked as potential malware. In the 1.0.2 version I added a locking feature to help harden your system from unwanted changes, especially to your hosts file.

When launched a simple GUI is opened that allows you to add one or many URLs (1 URL per line) that will then add those URLs to your hosts file. For example, if you enter in google.com as the URL, when you click on Add URLs button, it will add a line to your hosts file (C:\Windows\System32\drivers\etc\hosts) 127.0.0.1 google.com

When this is done, it will block the local computer from resolving google.com as it will resolve as 127.0.0.1. Please also note that for some websites in order to successfully block the URLs will need to have google.com and www.google.com to effectively block the URL. You may also choose from the dropdown menu list which once chosen will add to your unlocked hosts file. The 1.0.1 update also includes the ability to upload a URL list document for bulk domain/ip blocking. It also has a Flush DNS option that simply runs the ipconfig /flushdns command to flush the DNS resolver cache for the workstation

# Version 1.0.2:
![HostsFileURLBlocker1 0 2](https://user-images.githubusercontent.com/130707762/232276484-724edd76-23c0-4957-b3f4-a785d1be5d3b.PNG)

I made this as I am a computer repair technician and have seen many systems come into our shop with the OneLaunch adware that seems to be an attack vector for scammers to deliver malicious ads to call the scammers. Almost every system that comes in with a full system compromise has had OneLaunch installed shortly before a scammer was able to convince the user to install a remote access software such as AnyDesk.

Hope you find this useful :)

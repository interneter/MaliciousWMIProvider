# MaliciousWMIProvider
PoC for malicious code executed every given interval using WMI without any wmi-consumer.
This is a sample code taken from Microsoft docs combined with basic command parser & communication module in order to demonstrate malicious use.
The magic happens in the mof files where you create __EventFilter that query the malicious class, which executes the malicious code inside the WMI Provider.
After that, you will notice that the malicious code will be executed under WmiPrvSE.exe process, without any other process.

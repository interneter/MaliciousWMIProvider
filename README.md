# MaliciousWMIProvider
PoC for malicious code execution every fixed-given interval using WMI without any wmi-consumer (or filter to consuemr binding).
To achieve that goal, wmi provider was written (using microsoft docs sample).
The magic happens in the mof files where you create __EventFilter that query the malicious class, which executes the malicious code inside the WMI Provider.
After that, you will notice that the malicious code will be executed under WmiPrvSE.exe process, without any dedicated process.

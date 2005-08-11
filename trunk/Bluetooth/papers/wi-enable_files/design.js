// $Id: design.js,v 1.1.1.1 2005/07/08 14:31:04 charles Exp $
// Copyright 2005 IBM Corporation

function ibmCommonDesignVersion() {
var a;
var ibmv11, ibmv14, lenovo;

ibmv11 = ibmv14 = lenovo = false;

if (document.getElementsByTagName) {
for (var i = 0; (a = document.getElementsByTagName("link")[i]); i++) {
if (a.getAttribute("rel").indexOf("style") != -1) {
if (a.getAttribute("href").indexOf("//www.lenovo.com/common/v14/") != -1) { lenovo = "lenovo-think-v14"; }
else if (a.getAttribute("href").indexOf("//www.lenovo.com/common/l14/") != -1) { lenovo = lenovo || "lenovo-v14"; break; }
else if (a.getAttribute("href").indexOf("//www.ibm.com/common/v14/") != -1) { ibmv14 = "ibm-v14"; }
else if (a.getAttribute("href").indexOf("//www.ibm.com/data/css/v11/") != -1) { ibmv11 = "ibm-v11"; }
}
}
}
return (lenovo || ibmv14 || ibmv11 || "unknown");
}
//
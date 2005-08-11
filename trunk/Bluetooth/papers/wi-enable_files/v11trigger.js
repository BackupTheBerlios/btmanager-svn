// $Id: v11trigger.js,v 1.1.1.1 2005/07/08 14:31:04 charles Exp $
// CVM survey trigger
//
// contact: Scott Cale/New York, Corporate Webmaster team
//
// 1) Check for browser capabilities of storing cookies
// 2) Look for 'msp' blackout cookie
// 3) if not found and if random number is greater than fixed trigger -> link to pupLoc opening a new window

// ******************************
// Function to test user's browser for cookies
// ******************************
// return true if it's ok (from a cookie perspective) to invite this user
// return false otherwise
// this function replaces the existing cookie checks as per ManageNow #22423318

//
//
// ***** WARNING *****
//
// This version contains code used for troubleshooting the 
// ongoing Partner Commerce issue.  Do not leave this version
// up any longer than necessary
//
// Scott
//
//

if( typeof(ibmSurveyTest) == 'undefined' ){
	var ibmSurveyTest;
}

ibmSurveyTest = 'v11trigger.js loaded';

function ibmSurveyAllowsCookies(){
	if (typeof ibmCommonCookie == 'undefined') {
		ibmSurveyTest = 'common cookie failed to load';
		return false;			// cookie library did not load
	}

	var c = new ibmCommonCookie();
	var name = "msp";		// cookie name
	var timeout = 60;		// cookie ttl in seconds
	var maxCookies = 17;		// ignore users that have more than this many cookies

	if (c.getCookie(name)) {
		ibmSurveyTest = 'msp found';
		return false;		// cookie already exists
	}

	if (typeof(document.cookie) == 'string' && document.cookie && document.cookie.split) {
		if ((document.cookie.split('; ')).length > maxCookies) {
			ibmSurveyTest =  'too many cookies';
			return false;	// max cookies reached
		}
	}

	// set permantent cookie to verify that permanent cookies are enabled
	c.setCookie(name, 'enabled', timeout, '/', '.ibm.com');
	if (c.getCookie(name) == 'enabled') {
		c.deleteCookie(name, '/', '.ibm.com');
		return true;
	}
	else {
		ibmSurveyTest = 'cookies disabled';
		return false;
	}
}


// ******************************
// Function to link to PerlScript
// ******************************
function ibmSurveyPopup(CountryCode,LanguageCode,eSite,ShowPopTrigger) {

	var rdnum = Math.random();
	var attr ="toolbar=no,menubar=no,scrollbars=yes,resizable=yes,width=570,height=430";

	//do not launch from Lenovo-branded pages
	if( String(ibmCommonDesignVersion()).indexOf("lenovo") >= 0 ){
		ibmSurveyTest = 'lenovo branded';
		return false;
	}

	if( eSite == "cvm" ){
		attr="toolbar=no,menubar=no,scrollbars=yes,resizable=yes,width=570,height=318";
	}


	if (rdnum <  ShowPopTrigger) {
		ibmSurveyTest = 'user selected';
		pupLoc = "https://www.ibm.com";

		if( (typeof(staging) != "undefined") && (staging == "yes")){
			pupLoc = "//wwwstage.ibm.com";
		}

		// As per Jan 4, 2005 email from Andrea.
		//  We split all uscvm surveys into seperate directories
		//  which means we need to copy the "module" var over the "eSite" var
		if ( (eSite == "cvm") && (country == "us")
		 && (typeof(module) != "undefined") && (module != null) ){
			eSite = module;
		}


		pupLoc += "/cgi-bin/survey/esites/popup.pl?lang=" + LanguageCode + "&country=" + CountryCode + "&site=" + eSite;

		if( (typeof(version) != "undefined") && (version != null) ){
			pupLoc += "&version=" + version;
		}

		if( (typeof(module) != "undefined") && (module != null) ){
			pupLoc += "&module=" + module;
		}

		//Add escaped URL information to the pupLoc value
		var parent = location.href;
		//SC: strip off anchor if any. Jan 24, 2004 MN#22522776
		var pos = parent.indexOf("#");
		if( pos >= 0 ){
			parent = parent.substr(0,pos);
		}
		parent = escape(parent);
		pupLoc += "&URL=" + parent;

		zview=window.open(pupLoc,"view",attr);
	}
}


// **********************
// Main
// **********************

//check that we have all necessary params as per tracker ticket #1360-KRU
if( typeof(rate) != "undefined"){
	rate = parseFloat(rate);
}

if(	     (typeof(country)  != "undefined")  && (country)
	  && (typeof(language) != "undefined")  && (language)
	  && (typeof(site)     != "undefined")  && (site)
	  && (typeof(rate)     != "undefined")  && ( !(isNaN(rate)) )
	  && (rate > 0) ){

	if(       typeof(ibmCommonDesignVersion) != 'undefined'
		   && ibmSurveyAllowsCookies() ){
		ibmSurveyPopup(country, language, site, rate);
	} else {
		ibmSurveyTest += ' |failed design/cookie test';
	}
} else {
	ibmSurveyTest += ' |failed param check';
}


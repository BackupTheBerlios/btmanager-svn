// $Id: popup.js,v 1.1.1.1 2005/07/08 14:31:04 charles Exp $
// Contact: Scott Cale/New York
//          ibm.com Corporate Webmaster team

// We need to load the common/cookie code before the code that uses it.
// Therefore, I had to shift the original popup.js into v11trigger.js

var ibmSurveyServer = '//www.ibm.com';

if( (typeof staging != 'undefined') && (staging == 'yes') ){
	ibmSurveyServer = '//wwwstage.ibm.com';
}

if( typeof ibmCommonDesignVersion == 'undefined' ){
	document.write('<script type="text/javascript" language="JavaScript1.2" src="' + ibmSurveyServer + '/common/design.js"></script>');
}

if (typeof ibmCommonCookie == 'undefined') {
document.write('<script type="text/javascript" language="JavaScript1.2" src="' + ibmSurveyServer + '/common/cookie/cookie.js"></script>');
}

document.write('<script type="text/javascript" language="JavaScript1.2" src="' + ibmSurveyServer + '/survey/v11trigger.js"></script>');


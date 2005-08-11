// Copyright (c) 2004 IBM Corp. All rights reserved.
// IBM cookie library based on http://www.dithered.com/javascript/cookies/index.html maintained by Chris Nott
// $Id: cookie.js,v 1.1.1.1 2005/07/08 14:31:04 charles Exp $

function ibmCommonCookie() { 1; }
new ibmCommonCookie();

// Write a cookie value
ibmCommonCookie.prototype.setCookie = function(name, value, expires, path, domain, secure) {

var expiresDate = null;
if (expires) {
if (expires.toGMTString) {
expiresDate = expires;
}
else if (typeof(expires) == "number") {
expiresDate = new Date();
expiresDate.setTime(expiresDate.getTime() + 1000 * parseInt(expires));
}
}

document.cookie = name + '=' + escape(value) + ((expiresDate) ? '; expires=' + expiresDate.toGMTString() : '') + ((path) ? '; path=' + path : '') + ((domain) ? '; domain=' + domain : '') + ((secure) ? '; secure' : '');
}

// Retrieve a named cookie value
ibmCommonCookie.prototype.getCookie = function(name) {
var dc = document.cookie;

// find beginning of cookie value in document.cookie
// Note: cookie with more specific path comes first!
var prefix = name + "=";
var begin = dc.indexOf(prefix);
if (begin == -1) {
return null;
}
else if (begin > 0) {
begin = dc.indexOf("; " + prefix);
if (begin == -1) {
return null;
}
else {
begin += 2;
}
}

// find end of cookie value
var end = document.cookie.indexOf(";", begin);
if (end == -1) end = dc.length;

// return cookie value
return unescape(dc.substring(begin + prefix.length, end));
}

// Delete a named cookie value
ibmCommonCookie.prototype.deleteCookie = function(name, path, domain) {
var value = this.getCookie(name);
if (value != null) document.cookie = name + '=' + ((path) ? '; path=' + path : '') + ((domain) ? '; domain=' + domain : '') + '; expires=Thu, 01-Jan-70 00:00:01 GMT';
return value;
}

// Verify if user preferences allow setting cookies
ibmCommonCookie.prototype.allowsCookies = function(expires, path, domain, secure) {
var name = "allowsCookies";
var value = Math.random();

this.setCookie(name, value, ((expires) ? expires : ''), ((path) ? path : ''), ((domain) ? domain : ''), ((secure) ? secure : ''));

if (this.getCookie(name) == value) {
this.deleteCookie(name, path, domain);
return true;
}
else {
return false;
}
}

// Verify if user preferences allow setting session cookies
ibmCommonCookie.prototype.supportsCookies = function(path) {
return this.allowsCookies(0, ((path) ? path : ''));
}

// Hack to make the "instance" methods available as "class" methods also
var ibmCommonCookieObject = new ibmCommonCookie();
ibmCommonCookie.getCookie = ibmCommonCookieObject.getCookie;
ibmCommonCookie.setCookie = ibmCommonCookieObject.setCookie;
ibmCommonCookie.deleteCookie = ibmCommonCookieObject.deleteCookie;
ibmCommonCookie.allowsCookies = ibmCommonCookieObject.allowsCookies;
ibmCommonCookie.supportsCookies = ibmCommonCookieObject.supportsCookies;

//

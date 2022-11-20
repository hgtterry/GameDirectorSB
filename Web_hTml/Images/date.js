
// Days
var days = new Array;
days[0] = "Sunday";
days[1] = "Monday";
days[2] = "Tuesday";
days[3] = "Wednesday";
days[4] = "Thursday";
days[5] = "Friday";
days[6] = "Saturday";

// Months
var months = new Array;
months[0]  = "January";
months[1]  = "February";
months[2]  = "March";
months[3]  = "April";
months[4]  = "May";
months[5]  = "June";
months[6]  = "July";
months[7]  = "August";
months[8]  = "September";
months[9]  = "October";
months[10] = "November";
months[11] = "December";

// Get Current Date
var d = new Date();

// Get Parts
var curDay   = d.getDay();
var curMonth = d.getMonth();
var curDate  = d.getDate();
var curYear  = d.getFullYear();

// Format Strings
var strDate = days[curDay] + ", " + months[curMonth] + " " + curDate + ", " + curYear;

// Write Out
document.write(strDate);

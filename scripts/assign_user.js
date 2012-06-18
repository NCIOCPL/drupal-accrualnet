function submitChosenUser(user_id, value, nid, vid, role)
{
	// set up the request
	var xmlhttp;
	if (window.XMLHttpRequest)
	{
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}

	// define the callback, should only display errors
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			if(xmlhttp.responseText != "")
				alert("Received response:\n" + xmlhttp.responseText);
		}
	}

	// post the resource id, revision id, role, and user id
	xmlhttp.open("POST","/sites/accrualnet.cancer.gov/scripts/assign_user.php",true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	var post_string = "user_id=" + user_id + "&account_id=" + value + "&nid=" + nid + "&vid=" + vid + "&role=" + role;
	xmlhttp.send(post_string);
}
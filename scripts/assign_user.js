function submitChosenUser(user_id, value, nid, vid, role)
{
	var id = "assigned_to_" + nid;

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
			var element = document.getElementById(id);
			var text = xmlhttp.responseText;
			if(text != "")
			{
				if(text.length > 20)
					alert("Received response:\n" + xmlhttp.responseText);
				else
					element.innerHTML = text;
			}
			else
			{
				element.innerHTML = "no response.";
			}
		}
	}

	// post the resource id, revision id, role, and user id
	xmlhttp.open("POST","/sites/accrualnet.cancer.gov/scripts/assign_user.php",true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	var post_string = "user_id=" + user_id + "&account_id=" + value + "&nid=" + nid + "&vid=" + vid + "&role=" + role;
	xmlhttp.send(post_string);

	var element = document.getElementById(id);
	element.innerHTML = "working...";
}
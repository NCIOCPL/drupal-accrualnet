function submitChosenUser(display, value, nid, role)
{
	var id = display + "_assigned_to_" + nid;
	var selName = "assign_to_" + nid + "_select";

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
			var selects = document.getElementsByName(selName);
			var text = xmlhttp.responseText;
			if(text != "")
			{
				if(text.length > 20)
				{
					window.alert("Received response:\n" + xmlhttp.responseText);
					return;
				}

				// loop through the select elements found previously...
				for(var i = 0; i < selects.length; i++)
				{
					var select = selects.item(i);

					// check each option, and select the one that matches the
					// chosen value
					var options = select.options;
					for(var p = 0; p < options.length; p++)
					{
						var option = options[p];

						if(option.value == value)
						{
							// found the correct option, select it and move
							// to the next select
							select.selectedIndex = p;
							select.parentNode.nextSibling.innerHTML = xmlhttp.responseText;
							break;
						}
					}
				}
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
	var post_string = "&account_id=" + value + "&nid=" + nid + "&role=" + role;
	xmlhttp.send(post_string);

	var element = document.getElementById(id);
	element.innerHTML = "working...";
}
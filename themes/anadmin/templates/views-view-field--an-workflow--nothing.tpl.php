<?php

/**
 * This template is used to print a single field in a view. It is not
 * actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the
 * template is perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php

// load matching users from DB for intended roles if not set
if (!isset($_SESSION['current_users'])) {
	nci_workflow_session_fill_users('Writer');
	nci_workflow_session_fill_users('AccrualNet Staff');
}

// divide the given value into its components
list($nid, $state, $actions, $writer, $editor) = explode('|', $output);
$action_list = explode('<br />', $actions, -1);
$can_moderate = (isset($action_list[0]));

// make a simple array from the assigned users
$assigned_users = array(
	'Writer' => $writer,
	'AccrualNet Staff' => $editor
);

// get the appropriate role of users to list
$role = nci_workflow_get_role($state);

// print the current role:
//print $role . ': ';

// if users for the appropriate role are available...
if (isset($_SESSION['current_users'][$role])) {
	// and the current user can moderate the current state...
	if ($can_moderate) {
		global $user;

		$user_id = $user->uid;

		$display = $view->current_display;
		$div_id = "${display}_assigned_to_$nid";
		$sel_name = "assign_to_${nid}_select";

		// generate a select list
		print '<form autocomplete="off">';
		print "<select name=$sel_name onchange='submitChosenUser(\"$display\", this.value, $nid, \"$role\")'>";
		print '<option value="">- none -</option>';
		foreach ($_SESSION['current_users'][$role] as $id => $name) {
			print '<option';
			if ($assigned_users[$role] == $id)
				print ' selected="selected"';
			print ' value="' . $id . '">' . $name . '</option>';
		}
		print '</select>';
		print '</form>';

		// add a div to receive return output
		print "<div class='assign_to_status' id='$div_id'>&nbsp</div>";
		return;
	} else {
		// if the user can't moderate, just display the current user
		$id = $assigned_users[$role];
		if (isset($_SESSION['current_users'][$role][$id])) {
			print $_SESSION['current_users'][$role][$id];
			return;
		}
	}
}

// finally, just show as unassigned if arrrived at this point
print '<i>unassigned</i>';
?>

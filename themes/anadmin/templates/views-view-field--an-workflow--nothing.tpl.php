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

// get the appropriate role of users to list
$role = nci_workflow_get_role($state);

// choose between the assigned writer and editor
$assigned_user = '';
switch($role)
{
	case 'Writer':
		$assigned_user = $writer;
		break;
	case 'AccrualNet Staff':
		$assigned_user = $editor;
		break;
	default:
}

// if users for the appropriate role are available...
if (isset($_SESSION['current_users'][$role])) {
	$current_users = $_SESSION['current_users'][$role];

	// and the current user can moderate the current state...
	if ($can_moderate) {

		// retrieve the workflow assign users form and render it
		print drupal_render(drupal_get_form('nci_workflow_assign_form',
								$nid, $role, $assigned_user,
								$current_users));

		// done!
		return;
	} else {
		// if the user can't moderate, just display the current user
		if (isset($current_users[$assigned_user])) {
			print check_plain($current_users[$assigned_user]);
			return;
		}
	}
}

// finally, just show as unassigned if arrrived at this point
print '<i>unassigned</i>';
?>

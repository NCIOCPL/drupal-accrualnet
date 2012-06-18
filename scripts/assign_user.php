<?php

@ini_set('log_errors', 'On'); // enable or disable php error logging (use 'On' or 'Off')
@ini_set('display_errors', 'On'); // enable or disable public display of errors (use 'On' or 'Off')
@ini_set('error_log', '/logs/php-errors.log'); // path to server-writable log file
// must define DRUPAL_ROOT as the root of the site's filesystem
chdir('../../..');
$dir = getcwd();
define('DRUPAL_ROOT', $dir);

// Bootstrap Drupal up through the database phase.
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// define the DB values needed for the various roles
$role_db_map = array(
	'Writer' => array(
		'data_table' => 'an_field_data_field_assigned_writer',
		'rev_table' => 'an_field_revision_field_assigned_writer',
		'data_stem' => 'field_data_field_assigned_writer',
		'rev_stem' => 'field_revision_field_assigned_writer',
		'column' => 'field_assigned_writer_value',
		'field' => 'field_assigned_writer'
	),
	'AccrualNet Staff' => array(
		'data_table' => 'an_field_data_field_assigned_editor',
		'rev_table' => 'an_field_revision_field_assigned_editor',
		'data_stem' => 'field_data_field_assigned_editor',
		'rev_stem' => 'field_revision_field_assigned_editor',
		'column' => 'field_assigned_editor_value',
		'field' => 'field_assigned_editor'
	)
);

// retrieve the values from the POST
$user_id = $_POST['user_id'];
$nid = $_POST['nid'];
$vid = $_POST['vid'];
$role = $_POST['role'];
$account_id = $_POST['account_id'];

// validate posted values
if (!(isset($nid)
		&& is_numeric($nid)
		&& isset($vid)
		&& is_numeric($vid)
		&& isset($role)
		&& isset($role_db_map[$role])
		&& ($uid == ''
		|| is_numeric($uid))
		)) {
	echo 'BAD VALUES - ';
	echo $nid . ':' . $vid . ':' . $role . ':' . $account_id . ' ';
	return;
}

// verify that the given revision is still valid
$query = 'SELECT nid, vid ' .
		'FROM an_node_revision ' .
		'WHERE nid = ' . $nid . ' ' .
		'ORDER BY vid DESC ' .
		'LIMIT 1 ';

try {
	$result = db_query($query);
} catch (Exception $e) {
	echo print_r($e, TRUE);
	return;
}

foreach ($result as $record) {
	$revisions[] = $record;
}

// an empty result set or mismatch revision id indicates that
// no revision exists or doesn't match page's revision
if (!isset($revisions[0]) || $revisions[0]->vid != $vid) {
	echo 'Revision ' . vid . ' not current for node ' . $nid . '!';
	return;
}

// if the user isn't being cleared...
if (!empty($account_id)) {
// check that the indicated user has the correct role
	$query = 'SELECT an_users_roles.uid, an_users_roles.rid, an_role.name AS role_name ' .
			'FROM an_users_roles ' .
			'INNER JOIN an_role ' .
			'ON an_users_roles.rid = an_role.rid ' .
			'WHERE an_role.name in (\'' . $role . '\') ' .
			'AND an_users_roles.uid = ' . $account_id;

	try {
		$result = db_query($query);
	} catch (Exception $e) {
		echo print_r($e, TRUE);
		return;
	}

	foreach ($result as $record) {
		$returned_users[] = $record;
	}

	// an empty result set indicates that the uid and role combo could
	// not be found
	if (!isset($returned_users[0])) {
		echo 'User ' . $account_id . ' not found for role ' . $role . '!';
		return;
	}
}

// set values for data and revision
$column = $role_db_map[$role]['column'];
$table = $role_db_map[$role]['data_table'];
$stem = $role_db_map[$role]['data_stem'];

nci_workflow_db_set_field_value($account_id, $table, $stem, $column, $nid, $vid);

$table = $role_db_map[$role]['rev_table'];
$stem = $role_db_map[$role]['rev_stem'];
nci_workflow_db_set_field_value($account_id, $table, $stem, $column, $nid, $vid);

try {
	// need to clear the cache for the fields
	// TODO: this is a little drastic, maybe.
	field_cache_clear();
} catch (Exception $e) {
	echo print_r($e, TRUE);
	return;
}

// now, have to cross-reference the fields' existance and if the value needs
// to be set or cleared, which will result in an update, insert, or drop.
// retrieve the current values, determines if updates or inserts are needed
// validated the revision and the intended assigned user,
// proceed with update
/* try {
  $num_updated = db_update($table_stem)
  ->fields(array($column => $uid))
  ->condition('entity_id', $nid)
  ->condition('revision_id', $vid)
  ->execute();
  } catch (Exception $e) {
  echo print_r($e, TRUE);
  return;
  }

  echo 'Updated successfully!'; */

// no errors during update, all should be well
// (could do final query to verify values are set as intended?)
?>

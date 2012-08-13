<?php

module_load_include('module', 'resource');
module_load_include('inc', 'resource', 'types');
module_load_include('inc', 'an_taxonomy', 'includes/resource.globals');
module_load_include('inc', 'an_reports', 'includes/reports.globals');

function reports_level_2_page($section) {
// grab the resource stylesheet
	$css_path = drupal_get_path('module', 'resource_page_templates');
	$css_path .= "/resources.css";
	drupal_add_css($css_path, array('type' => 'file'));

	global $an_reports_menu, $an_reports_fields_completed;

	$output = "";
	$section_info = NULL;
	$section_machine_name = str_replace('-', '_', $section);

	if (!isset($an_reports_menu[$section]))
		return $output;
	else
		$section_info = $an_reports_menu[$section];
	
	// set the page title based on the section info
	drupal_set_title($section_info['title']);

	$output .= "<div><h2>${section_info['title']}</h2><a href='/admin/reports/accrualnet/$section/export'>Export</a></div>";

	$function = "_${section_machine_name}_report";

	$results = $function(true);

// generate the pager, if it exists
	$pager = theme('pager');

	$output .= $pager;
	$output .= "<div class='report-block'>";
	$output .= "<div class='report-header'>";
	foreach ($results['columns'] as $key => $title) {
		$title = str_replace('|', '<br>', $title);
		$class = '';
		if (isset($an_reports_fields_completed[$key]['class']))
			$class = $an_reports_fields_completed[$key]['class'];
		$output .= "<div class='report-cell $class'>$title&nbsp;</div>";
	}
	$output .= "</div>";

	$row_count = 0;
	foreach ($results['rows'] as $row) {
		$zebra = ($row_count++ % 2) ? 'row-even ' : 'row-odd ';
		$output .= "<div class='report-row $zebra'>";
		foreach ($row as $key => $value) {
			$value = str_replace('|', ',<br>', $value);
			//$value = implode('<br>', $value);
			$class = '';
			if (isset($an_reports_fields_completed[$key]['class']))
				$class .= $an_reports_fields_completed[$key]['class'];
			$output .= "<div class='report-cell $class'>$value&nbsp;</div>";
		}

		$output .= "</div>";
	}
	$output .= "</div>";
	$output .= $pager;

	return $output;
}

function reports_level_2_export($section) {
	global $an_reports_menu;

	$section_info = NULL;
	$section_machine_name = str_replace('-', '_', $section);

	if (!isset($an_reports_menu[$section]))
		return $output;
	else
		$section_info = $an_reports_menu[$section];

// build the function name and call it
	$function = "_${section_machine_name}_report";
	$results = $function();

// build an array of value arrays for csv output
	$lines = array();

	$lines[] = str_replace(',', ';', $results['columns']);
	foreach ($results['rows'] as $row)
		$lines[] = str_replace(',', ';', $row);

// send response headers to the browser
	drupal_add_http_header('Content-Type', 'text/csv');
	drupal_add_http_header('Content-Disposition', "attachment;filename=$section.csv");

// open the output and write each line's array
	$fp = fopen('php://output', 'w');
	foreach ($lines as $line) {
		fputcsv($fp, $line);
	}

// close the output and exit
	fclose($fp);
	drupal_exit();
}

function _fields_completed_report() {
	global $an_reports_fields_completed;

// define a null-or-empty array
	$null_or_empty = array('null', '');

	$columns = array();
	$rows = array(0 => array());

	foreach ($an_reports_fields_completed as $key => $info) {
		if ($info['type'] == 'prop') {
			$query = new EntityFieldQuery();
			$count = $query
					->entityCondition('entity_type', 'user')
					->propertyCondition($key, $null_or_empty, 'NOT IN')
					->count()
					->execute();

			$columns[] = $info['title'];
			$rows[0][] = $count;
		} else {
			$query = new EntityFieldQuery();
			$count = $query
					->entityCondition('entity_type', 'user')
					->fieldCondition("field_$key", 'value', $null_or_empty, 'NOT IN')
					->count()
					->execute();

			$columns[] = $info['title'];
			$rows[0][] = $count;
		}
	}

	$count = _completed_user_count();

	$columns[] = 'Complete';
	$rows[0][] = $count;

	return array('columns' => $columns, 'rows' => $rows);
}

function _fields_completed_detailed_report($pager = false) {
	global $an_reports_fields_completed;

// define a null-or-empty array
	$null_or_empty = array('null', '');

	$columns = array();
	$rows = array();
	$results_per_page = 15;

	/* $query = db_select("users", 'u')
	  ->condition('u.name', $null_or_empty, 'NOT IN');

	  // add the pager if needed
	  if ($pager)
	  $query = $query
	  ->extend('PagerDefault')
	  ->limit($results_per_page);

	  // join each field table
	  foreach ($an_reports_fields_completed as $key => $info) {
	  // if property of user
	  if ($info['type'] == 'prop') {
	  $query->addField('u', $key);
	  }
	  // else field
	  else {
	  $table_alias = "{$key}_table";

	  $subquery = db_select("field_data_field_$key", $table_alias);
	  $subquery->addField($table_alias, 'entity_id', 'uid');
	  $subquery->addExpression("GROUP_CONCAT(field_{$key}_value SEPARATOR '|')", "value");
	  $subquery->groupBy("$table_alias.entity_id");

	  $query->leftJoin($subquery, $table_alias, "$table_alias.uid = u.uid");
	  $query->addField($table_alias, 'value', $key);
	  }
	  }

	  $results = $query->execute();

	  foreach ($results as $row => $record) {
	  $complete = true;
	  foreach ($record as $key => $value) {
	  // retrieve the info for the column
	  $info = $an_reports_fields_completed[$key];

	  // set the column header, if not set already
	  if (!isset($columns[$key]))
	  $columns[$key] = $info['title'];

	  // clear out zero-value properties
	  if ($value === '0' && $info['type'] === 'prop')
	  $value = NULL;

	  // block out password hashes
	  if ($key == 'pass')
	  $value = '*****';

	  // save the value
	  $rows[$row][$key] = $value;

	  // check for completeness
	  if (!isset($value))
	  $complete = false;
	  }

	  // add the complete column
	  $columns['complete'] = 'Completed';
	  $rows[$row]['complete'] = $complete ? 'complete' : 'incomplete';
	  } */

	$query = new EntityFieldQuery();
	$query = $query
			->entityCondition('entity_type', 'user')
			->propertyCondition('name', '', '!=')
			->entityOrderBy('entity_id', 'DESC');

	if ($pager) {
		$query = $query->pager($results_per_page);
	}

	$rows = array();

	$results = $query->execute();
	$users = user_load_multiple(array_keys($results['user']));

	foreach ($users as $uid => $account) {
		$row = array();
		$complete = true;
		foreach ($an_reports_fields_completed as $key => $info) {

			if ($key == 'pass')
				continue;

			// set the column header, if not set already
			if (!isset($columns[$key]))
				$columns[$key] = $info['title'];

			if ($info['type'] == 'prop') {
				if ($key == 'pass')
					$row[$key][] = '*****';
				else if ($key == 'picture' && isset($account->picture))
					$row[$key][] = 'yes';
				else
					$row[$key][] = $account->$key;
			} else {
				$items = field_get_items('user', $account, "field_$key");

				$row[$key] = array();
				if (is_array($items)) {
					foreach ($items as $item) {
						$rendered = field_view_value('user', $account, "field_$key", $item);
						if (isset($rendered['#markup']))
							$row[$key][] = $rendered['#markup'];
					}
				} else {
					$row[$key][] = $items;
				}
			}

			// collapse the row
			$row[$key] = implode('|', $row[$key]);

			if (empty($row[$key]))
				$complete = false;
		}

		// add the complete column
		$columns['complete'] = 'Completed';
		$row['complete'] = $complete ? 'complete' : 'incomplete';


		$rows[] = $row;
	}

	return array('columns' => $columns, 'rows' => $rows); //, 'tags' => $query->alterTags);
}

function _completed_user_count() {
	global $an_reports_fields_completed;

// define a null-or-empty array
	$null_or_empty = array('null', '');

// generate complete count
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'user');
	foreach ($an_reports_fields_completed as $key => $info) {
		if ($info['type'] == 'prop') {
			$query->propertyCondition($key, $null_or_empty, 'NOT IN');
		} else {
			$query->fieldCondition("field_$key", 'value', $null_or_empty, 'NOT IN');
		}
	}
	return $query->count()->execute();
}

function _user_activity_report() {

	$columns = array('Registered Users', 'Completed Profiles', 'Blocked Users',
		'Community Memberships');
	$rows = array(0 => array());

// add registered users count
	$query = new EntityFieldQuery();

	$rows[0]['registered users'] = $query
			->entityCondition('entity_type', 'user')
			->propertyCondition('status', 1)
			->count()
			->execute();

// add completed user count
	$rows[0]['completed profiles'] = _completed_user_count();

// add blocked users count
	$query = new EntityFieldQuery();

	$rows[0]['blocked users'] = $query
			->entityCondition('entity_type', 'user')
			->propertyCondition('status', 0)
			->count()
			->execute();

// add community members count
	$rows[0]['community memberships'] = db_select("og_membership", 'ogm')
			->condition('ogm.state', 1)
			->condition('ogm.entity_type', 'user')
			->fields('ogm', array('etid'))
			->distinct()
			->countQuery()
			->execute()
			->fetchField();

	return array('columns' => $columns, 'rows' => $rows);
}

function _communities_report() {
	$output = '';

	$columns = array('Community Memberships', 'Comments', 'Conversations');
	$rows = array(0 => array());

// add community members count
	$rows[0]['community memberships'] = db_select("og_membership", 'ogm')
			->condition('ogm.state', 1)
			->condition('ogm.entity_type', 'user')
			->fields('ogm', array('etid'))
			->distinct()
			->countQuery()
			->execute()
			->fetchField();

// add comments count
	$query = db_select("comment", 'c');
	$query->join('node', 'n', 'n.nid = c.nid');

	$rows[0]['comments'] = $query
			->fields('c', array('nid'))
			->condition('n.type', 'conversation')
			->countQuery()
			->execute()
			->fetchField();

// add conversation count
	$rows[0]['conversations'] = db_select('node', 'n')
			->fields('c', array('nid'))
			->condition('n.type', 'conversation')
			->countQuery()
			->execute()
			->fetchField();

	return array('columns' => $columns, 'rows' => $rows);
}

function _community_activity_report() {
	$columns = array();
	$rows = array();

// set up the column headers and empty cells
	$columns[] = 'Group';
	$columns[] = 'Users';
	$columns[] = 'Conversations';
	$columns[] = 'Responses';

// for each community...
	$query = db_select('og', 'og');
	$query->condition('og.gid', 0, '<>')
			->fields('og', array('gid', 'label'));
	$result = $query->execute();

	foreach ($result as $record) {
		$gid = $record->{'gid'};
		$label = $record->{'label'};
		$row = array();
		$row['label'] = $label;

// retrieve user count
		$row['users'] = db_select("field_data_group_audience", 'ga')
				->condition('ga.group_audience_gid', $gid)
				->condition('ga.bundle', 'user')
				->fields('ga', array('entity_id'))
				->countQuery()
				->execute()
				->fetchField();

// retrieve conversation count
		$row['conversations'] = db_select("field_data_group_audience", 'ga')
				->condition('ga.group_audience_gid', $gid)
				->condition('ga.bundle', 'conversation')
				->fields('ga', array('entity_id'))
				->countQuery()
				->execute()
				->fetchField();

// retrieve response count
		$comm_query = db_select("comment", 'c');
		$comm_query->join('field_data_group_audience', 'ga', 'ga.entity_id = c.nid');

		$row['responses'] = $comm_query->fields('c', array('cid'))
				->condition('ga.bundle', 'conversation')
				->condition('ga.group_audience_gid', $gid)
				->countQuery()
				->execute()
				->fetchField();

		$rows[] = $row;
	}

	return array('columns' => $columns, 'rows' => $rows);
}
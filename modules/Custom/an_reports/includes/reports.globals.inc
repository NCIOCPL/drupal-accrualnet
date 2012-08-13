<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//The resources menu will be built based upon the vocabulary of these
//5 sections. If system names below  will change, these must be changed to map to
//the correct machine names.
$GLOBALS['an_reports_menu'] = array(
	'user-activity' => array('title' => "User Activity"),
	'communities' => array('title' => "Communities"),
	'community-activity' => array('title' => "Community Activity"),
	'fields-completed' => array('title' => "Fields Completed"),
	'fields-completed-detailed' => array('title' => "Fields Completed (detailed)"),
);

$GLOBALS['an_reports_fields_completed'] = array(
	'name' => array(
		'title' => 'User Name',
		'type' => 'prop'),
	'mail' => array(
		'title' => 'Email',
		'type' => 'prop',
		'class' => 'report-cell-wide'),
	'pass' => array(
		'title' => 'Password',
		'type' => 'prop',
		'class' => 'report-cell-narrow'),
	'occupation' => array(
		'title' => 'Occupation',
		'type' => 'field',
		'class' => 'report-cell-wide'),
	'years_in_research' => array(
		'title' => 'Years in Research',
		'type' => 'field'),
	'institution_type' => array(
		'title' => 'Institution Type',
		'type' => 'field'),
	'areas_of_interest' => array(
		'title' => 'Areas of Interest',
		'type' => 'field'),
	'picture' => array(
		'title' => 'Picture',
		'type' => 'prop',
		'class' => 'report-cell-narrow'),
);
?>

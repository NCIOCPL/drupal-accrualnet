<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.
$form['actions']['submit']['#value'] = "Submit for Review";

$doNotRender = array(
	'menu',
	'revision_information',
	'path',
	'comment_settings',
	'author',
	
);
/*
foreach ($doNotRender as $field) {
	$form[$field]['#access'] = FALSE;
	$form[$field]['#type'] = 'hidden';
	$form[$field]['#group'] = '';
	hide($form[$field]);
}
kprint_r($form);
*/
print drupal_render_children($form);
?>
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

print drupal_render_children($form);
?>
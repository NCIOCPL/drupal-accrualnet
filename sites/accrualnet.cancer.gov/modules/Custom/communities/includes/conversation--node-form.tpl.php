<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.

$form['group_content_access']['#prefix'] = '<div style="display:none;">';
$form['group_content_access']['#suffix'] = '</div>';
//hide($form['group_content_access']);


print drupal_render_children($form);
?>
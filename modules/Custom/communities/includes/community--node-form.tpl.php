<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.
$form['actions']['submit']['#value'] = "Submit for Review";

print drupal_render($form['title']);
print drupal_render($form['body']);
print drupal_render($form['actions']);
?>
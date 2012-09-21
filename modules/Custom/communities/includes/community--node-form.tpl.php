<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.

// Hide the checkbox for if it's a group or not
// hide() doesn't save as entity
$form['group_group']['#prefix'] = '<div style="display:none;">';
$form['group_group']['#suffix'] = '</div>';

// Hid the Group visibility if it's set correctly to private
if ($form['group_access']['und']['#default_value'] == 1) {
    //hide($form['group_access']); Does save as entity
    $form['group_access']['#prefix'] = '<div style="display:none;">';
    $form['group_access']['#suffix'] = '</div>';
}

// Change the Submit button to "Approved"
$form['actions']['submit']['#value'] = 'Approved';


print drupal_render_children($form);
?>
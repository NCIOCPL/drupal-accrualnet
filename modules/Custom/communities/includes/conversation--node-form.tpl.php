<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.

kprint_r(get_defined_vars());
hide($form['group_content_access']);


print drupal_render_children($form);
?>
<?php

// Change the text on the Submit button from "Save" to "Submit for Review" 
// because the default is not to publish the group.


hide($form['group_content_access']);


print drupal_render_children($form);
?>
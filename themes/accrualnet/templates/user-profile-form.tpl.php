<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>

<p>
	<?php print render($intro_text); ?>
</p>
<section class="column sidebar region profile-sidebar">
	<?php print render($form['picture']); ?>
</section>
<section class="column profile-content">
	<div class="accrualnet-user-profile-form-wrapper">
		<?php print drupal_render_children($form) ?>
	</div>
</section>
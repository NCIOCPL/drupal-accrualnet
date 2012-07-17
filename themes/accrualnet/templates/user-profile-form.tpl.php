<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//kprint_r($form);


// Form Changes
//kprint_r($form['account']);
$form['account']['name']['#title'] = "";
$output = "";
?>

<p>
	<?php print render($intro_text); ?>
</p>
<section class="column sidebar region profile-sidebar">
    
    <?php
            print drupal_render($form['picture']);
    
    ?>
    <!--img class="image" src="/<?php //print path_to_theme(); ?>/accrualnet-internals/images/global/test.jpg" /-->
</section>
<section class="column profile-content">
	<div class="accrualnet-user-profile-form-wrapper">
		<?php
                $output .= print drupal_render_children($form);
                //$output .= drupal_render($form['account']);
                //$output = str_replace('*', '<img src="/'.path_to_theme().'/accrualnet-internals/images/global/test.jpg" />', $output);
                print $output
                ?>
	</div>
</section>
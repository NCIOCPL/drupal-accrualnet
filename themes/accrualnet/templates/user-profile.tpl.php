<?php
/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 */
module_load_include('inc', 'nci_custom_user', 'includes\profilecolors');
global $nci_user_profile_colors;


$account = $elements['#account'];
$profileColor = 'Black';
if ($account->profile_color != NULL) {
    $profileColor = $nci_user_profile_colors[$account->profile_color['und'][0]['value']];
}

if (array_key_exists('avatar_image', $variables)) {
    $simulatedAvatarArray = array();
    foreach ($nci_user_profile_colors as $color) {
        $simulatedAvatarArray[] = 'male/'.$color;
        $simulatedAvatarArray[] = 'female/'.$color;
    }
    $avatarTMP = $avatar_image[0]['value'];
    $avatarTMP = $simulatedAvatarArray[$avatarTMP];
    $avatarSRC = '/' . path_to_theme() . '/accrualnet-internals/images/avatars/' . $avatarTMP . '.png';
    drupal_add_js("
        (function ($) {
        $(document).ready(function() {
            $('.user-picture').children('a').children('img').attr('src', '".$avatarSRC."');
            $('.user-picture').children('a').children('img').css('width', '200px');
        });
    }) (jQuery);
        ", 'inline');
}

$toHide = array('field_work_email', 'summary', 'profile_color', 'avatar_image', 'group_audience');
foreach ($toHide as $hideMe) {
    if (array_key_exists($hideMe, $user_profile)) {
        hide($user_profile[$hideMe]);
    }
}
?>
<span class="nci-profile<?php print '-'.$profileColor; ?>">

<section class="column sidebar region profile-sidebar">
        
	<?php print drupal_render($user_profile['user_picture']); ?>
           
</section>
<section class="column profile-content">
    <h1 class="field-label"><?php print $account->name; ?></h1>
	<div class="profile"<?php print $attributes; ?>>
		<?php 
print drupal_render($user_profile); 
?>
	</div>
</section>
</span>
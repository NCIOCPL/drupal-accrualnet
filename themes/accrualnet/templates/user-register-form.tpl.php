<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
module_load_include('inc', 'nci_custom_user', 'includes\profilecolors');
global $nci_user_profile_colors;
$color = 'Black';
global $base_url;
// Give them access to change their username
$form['account']['name']['#access'] = TRUE;
// Form Changes
$form['account']['status']['#access'] = FALSE;
$path = path_to_theme();
$slash = strpos($path, '/') + 1;
$path = substr($path, 0, strpos($path, '/', $slash));
drupal_add_js(path_to_theme() . '/js/checkbox.js', 'file');
drupal_add_js(path_to_theme() . '/js/profilecolors.js', 'file');
drupal_add_js(path_to_theme() . '/js/selectboxes.js', 'file');
drupal_add_js(path_to_theme() . '/js/profilehelp.js', 'file');
drupal_add_js(path_to_theme() . '/js/profileavatars.js', 'file');
drupal_add_js(array('selectedValues' => array(), 'pathToTheme' => path_to_theme(), 'avatarfile' => ''), 'setting');

$output = '';
?>

<p>
    <?php print render($intro_text); ?>
</p>
<section>
    <div id="required-text"><span class="form-required"><img alt="Denotes a required field." class="required-img" src="/<?php print path_to_theme(); ?>/accrualnet-internals/images/global/required.png"/></span><i> Denotes a required field</i></div>
</section>
<section class="column sidebar region profile-sidebar">
    <?php print drupal_render($form['picture']); ?>
    <div class="profile-avatars-wrapper">
        <?php print drupal_render($form['avatar_image']); ?>
        <div class="profile-avatars-images">
            <div class="profile-avatars-male">
                <?php
                foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
                    if (isset($avatarIMG['gender']) && isset($avatarIMG['color']) &&
                            $avatarIMG['gender'] == 'male' && $avatarIMG['color'] == $colorOpt) {
                        print '<span tabIndex="0" class="avatar-option picked" id="' . $colorOpt . '" title="male">';
                    } else {
                        print '<span tabIndex="0" class="avatar-option" id="' . $colorOpt . '" title="male">';
                    }
                    $altText = "Male " . $colorOpt;
                    print '<img alt="' . $altText . '" src="/' . path_to_theme() . '/accrualnet-internals/images/avatars/male/' . $colorOpt . '.png" />';
                    print '</span>';
                }
                ?>
            </div>
            <div class="profile-avatars-female">
                <?php
                foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
                    if (isset($avatarIMG['gender']) && isset($avatarIMG['color']) &&
                            $avatarIMG['gender'] == 'female' && $avatarIMG['color'] == $colorOpt) {
                        print '<span tabIndex="0" class="avatar-option picked" id="' . $colorOpt . '" title="female">';
                    } else {
                        print '<span tabIndex="0" class="avatar-option" id="' . $colorOpt . '" title="female">';
                    }
                    $altText = "Female " . $colorOpt;
                    print '<img alt="' . $altText . '" src="/' . path_to_theme() . '/accrualnet-internals/images/avatars/female/' . $colorOpt . '.png" />';
                    print '</span>';
                }
                ?>
            </div>
        </div>

    </div>

    <br/><br/><br/>
    <div class="profile-colors-wrapper">
        <?php
        print drupal_render($form['profile_color']);
        ?>

        <div class="profile-colors-container">
            <div class="profile-colors-selected" id="<?php print $color; ?>"></div>
            <div class="profile-colors-options">
                <?php
                foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
                    print '<span tabIndex="0" class="profile-colors-option" id="' . $colorOpt . '" title="' . $colorValue . '"></span>';
                }
                ?>
            </div>
        </div>

    </div>
</section>
<section class="column profile-content">
    <div class="accrualnet-user-register-form-wrapper<?php print ' ' . $color; ?>">
        <?php
        print drupal_render($form['account']['name']);
        ?>
        <p id="username-warning">Note: Your username is how you will be publicly identified on this site.</p>
        <?php
        print drupal_render($form['account']['mail']);
        print drupal_render($form['account']['current_pass']);
        print drupal_render($form['account']['pass']);
        print drupal_render($form['account']['roles']);
        print drupal_render($form['field_occupation']);


        $selectOutputs = array('field_years_in_research', 'field_institution_type');
        foreach ($selectOutputs as $select) {

            $output .= drupal_render($form[$select]);
            if (count($form[$select]['und']) > 0) {
                $output .= '<div tabIndex="0" id="' . $select . '" class="selectBox">';
                $output .= '<span class="selected">';
                $output .='</span><span class="selectArrow">&#9660</span>';
                $output .= '<div class="selectOptions">';

                if (array_key_exists('#default_value', $form[$select]['und'])) {
                    $safeValue = NULL;
                    if ($form[$select]['und']['#default_value'] != NULL) {

                        if (array_key_exists('safe_value', $form[$select]['und']['#default_value'])) {
                            $safeValue = $form[$select]['und']['#default_value']['safe_value'];
                            if (!array_key_exists($safeValue, $form[$select]['und']['#options'])) {
                                $safeValue = "select_or_other";
                            }
                            foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                                if ($selectOptionValue == $safeValue)
                                    $class = 'selectOption selectedd';
                                else
                                    $class = 'selectOption';
                                $output .= '<span tabIndex="0" class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                            }
                        } else {
                            $index = $form[$select]['und']['#default_value'][0];

                            foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                                if ($selectOptionKey == $index)
                                    $class = 'selectOption selectedd';
                                else
                                    $class = 'selectOption';
                                $output .= '<span tabIndex="0" class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                            }
                        }
                    } else {
                        foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                            $output .= '<span tabIndex="0" class="selectOption" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                        }
                    }
                    if (array_key_exists('#other', $form[$select]['und'])) {
                        if ($safeValue == "select_or_other") {
                            $output .= '<span tabIndex="0" class="selectOption select_or_other selectedd">' . $form[$select]['und']['#other'] . '</span>';
                        } else {
                            $output .= '<span tabIndex="0" class="selectOption select_or_other">' . $form[$select]['und']['#other'] . '</span>';
                        }
                    }
                }

                $output .= '</div>';
                $output .= '<div class="select-spacer">&nbsp;</div>';
                $output .= '</div>';
            }
        }
        print $output;
        print drupal_render($form['field_areas_of_interest']);
        print drupal_render($form['actions']);

        print drupal_render_children($form);
        ?>
    </div>
</section>
<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


$form['account']['name']['#description'] = "?";
$form['account']['name']['#access'] = TRUE;
$form['account']['mail']['#description'] = "?";
$form['account']['current_pass']['#access'] = FALSE;
module_load_include('inc', 'nci_custom_user', 'includes\profilecolors');
global $nci_user_profile_colors;
print kprint_r($form);
$account = $form['account'];
$color = $nci_user_profile_colors[0];
if (count($form['profile_color']['und']) > 0) {
    if (array_key_exists('#value', $form['profile_color']['und'])) {
        if (count($form['profile_color']['und']['#value']) > 0) {
            $color = $nci_user_profile_colors[array_pop($form['profile_color']['und']['#value'])];
        }
    }
}

// Form Changes
//kprint_r($form['account']);
$form['account']['status']['#access'] = FALSE;
$form['account']['roles']['#access'] = FALSE;

$form['account']['name']['#title'] = "";
$form['account']['pass']['#title_display'] = "after";
$output = "";


/* drupal_add_js('Drupal.behaviors.password = function () {};', 'inline', 'header'); */
$selectedValuesOnLoad = array();
$selectedValuesFieldRole = $form['field_occupation']['und']['#default_value'];
foreach ($selectedValuesFieldRole as $selected) {
    if (!in_array($selected, $form['field_occupation']['und']['#options'])) {
        $selectedValuesOnLoad[] = "ROLE_OTHER";
    } else {
        $selectedValuesOnLoad[] = $selected;
    }
}
$selectedValuesFieldAOI = $form['field_areas_of_interest']['und']['#default_value'];
foreach ($selectedValuesFieldAOI as $selected) {
    if (!in_array($selected, $form['field_areas_of_interest']['und']['#options'])) {
        $selectedValuesOnLoad[] = "AOI_OTHER";
    } else {
        $selectedValuesOnLoad[] = $selected;
    }
}
//$selectedValuesOnLoad = array_merge($form['field_role']['und']['#default_value'], $form['field_areas_of_interest']['und']['#default_value']);
//$selectedValuesOnLoad = $form['field_role']['und']['#default_value'];
foreach ($selectedValuesOnLoad as &$value) {
    //$value = str_replace(' ', '-', $value);
}
drupal_add_js(path_to_theme() . '/js/checkbox.js', 'file');
drupal_add_js(path_to_theme() . '/js/profilecolors.js', 'file');
drupal_add_js(path_to_theme() . '/js/selectboxes.js', 'file');
drupal_add_js(path_to_theme() . '/js/inputdarken.js', 'file');
drupal_add_js(path_to_theme() . '/js/profilehelp.js', 'file');
drupal_add_js(path_to_theme() . '/js/profileavatars.js', 'file');
drupal_add_js(array('selectedValues' => $selectedValuesOnLoad, 'pathToTheme' => path_to_theme()), 'setting');
drupal_add_js("
    (function ($) {
        $(document).ready(function() {
            $('.form-required').html('<img class=\"required-img\" src=\"/".path_to_theme()."/accrualnet-internals/images/global/required.png\" />');
        
        });
    }) (jQuery);", 'inline');


$form['actions']['submit']['#value'] = 'Save Changes';
$form['actions']['cancel']['#value'] = 'Cancel';
 kprint_r($form['picture']['picture']['#value']);
?>

<p>
    <?php print render($intro_text); ?>
</p>


<section class="column sidebar region profile-sidebar">
    <?php print render($form['picture']); ?>
    <div class="profile-avatars-wrapper">
        <div class="form-item">
        <label>Choose Avatar</label>
        </div>
        <div class="profile-avatars-images">
        <div class="profile-avatars-male">
        <?php
        foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
            print '<span class="avatar-option" id="' . $colorOpt . '" title="male">';
            print '<img src="/' . path_to_theme() . '/accrualnet-internals/images/avatars/male/'.$colorOpt.'.png" />';
                print '</span>';
        }
        ?>
        </div>
                <div class="profile-avatars-female">
        <?php
        foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
            print '<span class="avatar-option" id="' . $colorOpt . '" title="female">';
            print '<img src="/' . path_to_theme() . '/accrualnet-internals/images/avatars/female/'.$colorOpt.'.png" />';
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
                    print '<span class="profile-colors-option" id="' . $colorOpt . '" title="' . $colorValue . '"></span>';
                }
                ?>
            </div>
        </div>

    </div>
</section>
<section class="column profile-content">
    <div class="accrualnet-user-profile-form-wrapper<?php print ' ' . $color; ?>">
        <?php
        //print drupal_render_children($form);

        $output .= drupal_render($form['account']['name']);
        $output .= drupal_render($form['account']['mail']);

        $output .= drupal_render($form['account']['pass']);

        $output .= drupal_render($form['field_occupation']);




        $selectOutputs = array('field_years_in_research', 'field_institution_type');
        foreach ($selectOutputs as $select) {
            $output .= drupal_render($form[$select]);
            if (count($form[$select]['und']) > 0) {
                $output .= '<div id="' . $select . '" class="selectBox">';
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
                                $output .= '<span class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                            }
                        } else {
                            $index = $form[$select]['und']['#default_value'][0];

                            foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                                if ($selectOptionKey == $index)
                                    $class = 'selectOption selectedd';
                                else
                                    $class = 'selectOption';
                                $output .= '<span class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                            }
                        }
                    } else {
                        foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                            $output .= '<span class="selectOption" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                        }
                    }
                    if (array_key_exists('#other', $form[$select]['und'])) {
                        if ($safeValue == "select_or_other") {
                            $output .= '<span class="selectOption select_or_other selectedd">' . $form[$select]['und']['#other'] . '</span>';
                        } else {
                            $output .= '<span class="selectOption select_or_other">' . $form[$select]['und']['#other'] . '</span>';
                        }
                    }
                }

                $output .= '</div>';
                $output .= '<div class="select-spacer">&nbsp;</div>';
                $output .= '</div>';
            }
        }
        $output .= drupal_render($form['field_areas_of_interest']);
        $output .= '<br/>';
        $output .= drupal_render($form['actions']);

        $output .= drupal_render_children($form);




//kprint_r(form_builder($form['#form_id'], $form['account']['pass'], NULL));
//                $output .= drupal_render($form['account']);
        //$output = str_replace('*', '<img src="/' . path_to_theme() . '/accrualnet-internals/images/global/required.png" />', $output);
        //$output = str_replace('<div class="description">', '<div class="description"><img src="/' . path_to_theme() . '/accrualnet-internals/images/global/help.png" />', $output);
        print $output;
        ?>
    </div>
</section>

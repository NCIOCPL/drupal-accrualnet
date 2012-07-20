/*
 * Added By: Lauren
 * Added On: July 13, 2012
 * 
 * Last Modified By: Lauren
 * Last Modified On: July 18, 2012
 * 
 * Controls the appearance of the checkboxes and what they select.
 */

(function ($) {

    $(document).ready(function(){

        // Hide all of the checkboxes
       $('.form-checkbox').css('display', 'none');

        // Get the values that a user already has selected
        var $selectedValues = Drupal.settings.selectedValues;
      
        // Error handling for the "select_or_other" module
        if (jQuery.inArray('ROLE_OTHER', $selectedValues, 0) >= 0) {
            $('.form-item-field-occupation-und-select-select-or-other').addClass('checked');
            $('input#edit-field-occupation-und-select-select-or-other').attr('checked', true);
            $('.form-item-field-occupation-und-select-select-or-other').parent().parent().next().css('display', 'block');
            $('.form-item-field-occupation-und-select-select-or-other').parent().parent().next().children('input').css('display', 'block');
        }
        if (jQuery.inArray('AOI_OTHER', $selectedValues, 0) >= 0) {
            $('.form-item-field-areas-of-interest-und-select-select-or-other').addClass('checked');
            $('input#edit-field-areas-of-interest-und-select-select-or-other').attr('checked', true);
            $('.form-item-field-areas-of-interest-und-select-select-or-other').parent().parent().next().css('display', 'block');
            $('.form-item-field-areas-of-interest-und-select-select-or-other').parent().parent().next().children('input').css('display', 'block');
        }

        // For every checkbox we have, figure out if it's supposed to start out 
        // as checked (e.g. User has already selected that value) or unchecked
        jQuery.each($('.form-type-checkbox'), function()  {
            // Get the value of the INPUT checkbox
            var $inputvalue = $(this).children('input').val();
            // Default is to be unchecked (aka not found as a preselected value)
            var $found = false;
            
            // Check to see any of the previously selected values that we have 
            // match this
            for (key in $selectedValues) {
                // If we find a match, make sure that the INPUT is checked to 
                // TRUE and add the checked CLASS (dark square).
                if ($selectedValues[key] == $inputvalue) {
                    $found = true;
                    $(this).addClass('checked');
                    $(this).children('input').attr('checked', true);
                    // No need to keep looping for this INPUT, we found what we 
                    // were looking for.
                    break;
                }
            }
            
            // If an item was not found AND not checked, then we must ensure that 
            // it does not have a checked attribute and that we add the unchecked 
            // CLASS (dark square).
            if (!$found && !$(this).hasClass('checked')) {
                $(this).addClass('unchecked');
                $(this).children('input').removeAttr('checked');
            }

        });
        

       
        // Every time we click on a DIV with a checkbox in it, we must toggle it.
        // Also, we must make sure to toggle the Other box if SELECT_OR_OTHER is
        // chosen.
        $('div.form-type-checkbox').click(function () {
            // First, determine if it's checked or unchecked so we don't
            // recalculate these values.
            var $isChecked = $(this).hasClass('checked');
            var $isUnchecked = $(this).hasClass('unchecked');

            // If it is already checked, uncheck it and remove that INPUT's
            // checked attribute. Else, do opposite.
            if ($isChecked) {
                $(this).addClass('unchecked');
                $(this).removeClass('checked');
                $(this).children('input').removeAttr('checked');
            } else if ($isUnchecked) {
                $(this).removeClass('unchecked');
                $(this).addClass('checked');
                $(this).children('input').attr('checked', 'checked');
            }
            
            if ($(this).children('input').val() == 'select_or_other') {
                $(this).parent().parent().next().toggle();
                $(this).parent().parent().next().children('input').toggle();
            }
            
              
            // Return FALSE so it doesn't loop through again.
            // DO NOT PUT "return false;" !!!!!!!!!!!!!!!!!!!
            // JS will not recognize this and this script will loop through twice.
            //return FALSE;    
            return false;
            // IDK... I had to add return false back in and now it works again.
            // I'm really not sure what's going on with this... Maybe ending 
            // both jQuery and JS scripts? But it works now.
            
            // Ok more investigation... return false will keep the non-Other values
            // from executing twice.
        });

    });
    
})(jQuery); 



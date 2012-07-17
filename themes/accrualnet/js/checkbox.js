/*
 * Added By: Lauren
 * Added On: July 13, 2012
 * 
 * Last Modified By: Lauren
 * Last Modified On: July 13, 2012
 * 
 * Controls the appearance of the checkboxes and what they select.
 */

(function ($) {

    $(document).ready(function(){
        $('.form-checkbox').css('display', 'none');
        /*.accrualnet-user-profile-form-wrapper .form-checkbox {*/
    
    /*display: none;*/
    
     
        

        
        var $selectedValues = Drupal.settings.selectedValues;
        alert($selectedValues);
        /*if (($selectedValues.index('ROLE_OTHER')) != -1) {*/
        if (jQuery.inArray('ROLE_OTHER', $selectedValues)) {
            $('.form-item-field-role-und-select-select-or-other').addClass('checked');
        }
        if (jQuery.inArray('AOI_OTHER', $selectedValues)) {
            $('.form-item-field-areas-of-interest-und-select-select-or-other').addClass('checked');
        }
        
        alert($selectedValues);
        jQuery.each($('.form-type-checkbox'), function()  {
            var $inputvalue = $(this).children('input').val();
            var $found = false;
            for (key in $selectedValues) {
    
                /*if ($clslst.indexOf($selectedValues[key]) > -1) {*/
                if ($selectedValues[key] == $inputvalue) {
                    $found = true;
                    /*$(this).find('label').addClass('checked');*/
                    $(this).addClass('checked');
                    $(this).attr('checked', true);
                    break;
                }
            }
            if (!$found || !$(this).hasClass('checked')) {
                /*$(this).find('label').addClass('unchecked');*/
                $(this).addClass('unchecked');
                $(this).removeAttr('checked');
            }
    
    

   
    
        });

        $('.form-type-checkbox').click(function () {
            if ($(this).hasClass('checked')) {
                $(this).addClass('unchecked');
                $(this).removeClass('checked');
                $(this).removeAttr('checked');
                return true;
            } else if ($(this).hasClass('unchecked')) {
                $(this).removeClass('unchecked');
                $(this).addClass('checked');
                $(this).attr('checked', 'checked');
                return true;
            }
            return false;
        });

    
    });
})(jQuery); 



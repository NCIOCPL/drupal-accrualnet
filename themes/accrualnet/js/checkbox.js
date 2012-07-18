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
        
        if (jQuery.inArray('ROLE_OTHER', $selectedValues, 0) >= 0) {
            $('.form-item-field-occupation-und-select-select-or-other').addClass('checked');
        }
        if (jQuery.inArray('AOI_OTHER', $selectedValues, 0) >= 0) {
            alert('wtf');
            $('.form-item-field-areas-of-interest-und-select-select-or-other').addClass('checked');
        }
    
        
        
        jQuery.each($('.form-type-checkbox'), function()  {
            var $inputvalue = $(this).children('input').val();
            var $found = false;
            for (key in $selectedValues) {
    
                if ($selectedValues[key] == $inputvalue) {
                    $found = true;
    
                    $(this).addClass('checked');
                    $(this).attr('checked', true);
                    break;
                }
            }
            if (!$found || !$(this).hasClass('checked')) {
                $(this).addClass('unchecked');
                $(this).removeAttr('checked');
            }
    
    

   
    
        });


       
        $('div.form-type-checkbox').click(function () {
            var $isChecked = $(this).hasClass('checked');
            var $isUnchecked = $(this).hasClass('unchecked');
            alert($(this).html());
            if ($isChecked) {
                $(this).addClass('unchecked');
                $(this).removeClass('checked');
                $(this).removeAttr('checked');
                
            } else if ($isUnchecked) {
                $(this).removeClass('unchecked');
                $(this).addClass('checked');
                $(this).attr('checked', 'checked');
                
            }
         
        });

    
    });
})(jQuery); 



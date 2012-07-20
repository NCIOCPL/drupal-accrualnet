/***
 * Added By: Lauren
 * Added On: July 16, 2012
 * 
 * Last Edited By: Lauren
 * Last Edited On: July 17, 2012
 * 
 * This stylizes the SELECT boxes for the profile page and sets their values.
 ***/


(function ($) {
    $(document).ready(function() {

        // Hide all of the select boxes now that this script is called.
        $('.form-type-select > select').css('display', 'none');

        // Move the created fake SELECT boxes into the surrounding DIV of the 
        // real SELECT boxes. This is required for recognizing the original
        // SELECT boxes and editing their values.
        if ($('.form-item-field-years-in-research-und').find('.description').html() != null) {
             $('#field_years_in_research').insertBefore($('.form-item-field-years-in-research-und > .description'));
        } else {
            $('#field_years_in_research').appendTo('.form-item-field-years-in-research-und');
        }
        if ($('.form-item-field-institution-type-und-select').find('.description').html() != null) {
            $('#field_institution_type').insertBefore($('.form-item-field-institution-type-und-select > .description'));
        } else {
        $('#field_institution_type').appendTo('.form-item-field-institution-type-und-select');
        }
        
        // Set the height of the spacer and set it to hide. This is needed for
        // padding of the menu as it slides up and down.
        $('div.select-spacer').each(function () {
            $(this).appendTo($(this).parent());
            $(this).height($(this).prev().height()+32);
            $(this).hide();
        });
        
        
        
        // I don't think this is needed, but I'm scared to delete it.
        $('div.select_or_other').click(function () {
            $(this).parent().parent().parent().next().css('display', 'block');
        });
        
        if ($('select#edit-field-institution-type-und-select').val() == 'select_or_other') {
            $('div.form-item-field-institution-type-und-other').css('display', 'block');
            $('input#edit-field-institution-type-und-other').css('display', 'block');
        }
        
        // This controls the fake SELECT box and its actions as it mimics and sets 
        // the original SELECT box.
        $('div.selectBox').each(function(){
            
            // Set the default displayed value to be the value that is set as 
            // selected.
            $(this).children('span.selected').html($(this).children('div.selectOptions').children('.selectedd').html());
            // Set the value of what's selected.
            $(this).attr('value',$(this).children('div.selectOptions').children('.selectedd').attr('value'));
            
            // When clicking on the arrow or in the selected box, toggle the 
            // options up or down. Also, change the colors and clear the
            // visible SELECTed option.
            $(this).children('span.selected,span.selectArrow').click(function(){
                // First, expand the border, then slide
                $(this).parent().css('border-width', '3px');
                
                // Toggle the options
                $(this).parent().children('div.selectOptions').slideToggle();
                $(this).parent().children('div.select-spacer').slideToggle();

                // Remove whatever is in the current SELECTed box
                $(this).parent().children('span.selected').html(" ");
            });

            // When selecting an OPTION, set the value accordingly and slide the 
            // options box back up. Also, be prepared to handle the INPUT field 
            // that appears if "OTHER" is selected.
            $(this).find('span.selectOption').click(function(){
                
                // Set the value to be what was just clicked on.
                $(this).closest('div.selectBox').attr('value',$(this).attr('value'));
                // Reflect the change in the collapsed box view.
                $(this).parent().siblings('span.selected').html($(this).html());
                
                // Remove the old selected class from the previous choice.
                $(this).parent().children('span.selectOption').removeClass('selectedd');
                // Add the class to the newly selected choice.
                $(this).addClass('selectedd');
                
                
                // Roll the options list back up.
                $(this).parent().slideUp();
                $(this).parent().parent().children('div.select-spacer').slideUp();

                // If OTHER was selected, make the INPUT box appear. If not, make
                // sure the box is hidden (as if it was previously selected and 
                // no longer desired).
                if ($(this).hasClass('select_or_other')) {
                    $(this).parent().parent().parent().children('select').val('select_or_other');
                    $(this).parent().parent().parent().parent().children('.form-type-textfield').toggle();
                    $(this).parent().parent().parent().parent().children('.form-type-textfield').children('input').toggle();
                } else {
                    $(this).parent().parent().parent().children('select').val($(this).attr('id'));
                    $(this).parent().parent().parent().parent().children('.form-type-textfield').toggle();
                    $(this).parent().parent().parent().parent().children('.form-type-textfield').children('input').toggle();
                }
                
                // Fix the border
                // This should be the last thing we do
                $(this).parent().parent().css('border-width', '1px');
                
            });
        });
    });

}) (jQuery);


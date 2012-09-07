/***
 * Added By: Lauren
 * Added On: July 16, 2012
 * 
 * Last Edited By: Lauren
 * Last Edited On: July 17, 2012
 * 
 * Changes the profile colors on the Edit User page.
 ***/

(function ($) {
    $(document).ready(function() {
        
        // When the page first loads, set the SELECT value to be that of which 
        // is already stored in the database.
        $('.profile-colors-option').each(function () {
            // Find the correct color to set the value properly
           if ($(this).attr('id') == $('.profile-colors-selected').attr('id')) {
               $('select#edit-profile-color-und').val($(this).attr('title'));
           }
        });

        
        
        // If the user clicks on one of the colors, change the colors in the 
        // rest of the form AND change the SELECT value.
        $('.profile-colors-option').click(function() {
            // The following line changes the SELECT value. This must change if 
            // the DIVs for Profile Colors are ever moved.
            $(this).parent().parent().prev().children('.form-item').children('select').val($(this).attr('title'));
            var $newid = $(this).attr('id'); // What color we're changing to
            var $oldid = $(this).parent().prev().attr('id'); // What the old color is
            // For everything that has that old color as a class, replace it 
            // with the new color
            $('.' + $(this).parent().prev().attr('id')).each(function () {
                $(this).removeClass($oldid);
                $(this).addClass($newid);
            });
            // Update the large selected color DIV
            $(this).parent().prev().attr('id', $(this).attr('id'));
        });
        
        
                // If the user clicks on one of the colors, change the colors in the 
        // rest of the form AND change the SELECT value.
                $('.profile-colors-option').keyup(function (e) {
                    var key = e.charCode ? e.charCode : e.keyCode ? e.keyCode : 0;
        if(key == 13) {
            // The following line changes the SELECT value. This must change if 
            // the DIVs for Profile Colors are ever moved.
            $(this).parent().parent().prev().children('.form-item').children('select').val($(this).attr('title'));
            var $newid = $(this).attr('id'); // What color we're changing to
            var $oldid = $(this).parent().prev().attr('id'); // What the old color is
            // For everything that has that old color as a class, replace it 
            // with the new color
            $('.' + $(this).parent().prev().attr('id')).each(function () {
                $(this).removeClass($oldid);
                $(this).addClass($newid);
            });
            // Update the large selected color DIV
            $(this).parent().prev().attr('id', $(this).attr('id'));
        }
        });
    });

}) (jQuery);

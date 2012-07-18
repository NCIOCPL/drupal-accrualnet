/***
 * Added By: Lauren
 * Added On: July 16, 2012
 * 
 * Last Edited By: Lauren
 * Last Edited On: July 17, 2012
 * 
 * This darkens the BORDER-COLOR of an INPUT box when editing it.
 ***/

(function ($) {
    $(document).ready(function() {

        // When the document first loads, nothing has been edited
        var $lastedit = null;
        
        // Whenever an input value is changed, it's color should be darkened
        $('.form-type-textfield > input, .form-type-password > input').click(function() {
            // If applicable, remove the last edited object's thicker border,
            // then set the last edited object to be what we just clicked on
            if ($lastedit == null) {
                $lastedit = $(this);
            } else {
                $lastedit.css('border-width', '1px');
                $lastedit = $(this);
            }
            
            // Increase the pixels of the border when editing
            $(this).css('border-width', '3px');
            
        });
        
    });
}) (jQuery);

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
        $('input').click(function() {
            // If applicable, remove the last edited object's darker border color,
            // then set the last edited object to be what we just clicked on
            if ($lastedit == null) {
                $lastedit = $(this);
            } else {
                $lastedit.css('border-color', '#D5FF87');
                $lastedit = $(this);
            }
            // Add the darkened CSS as a border color
            $(this).css('border-color', '#9AB83F');
        });
        
    });
}) (jQuery);

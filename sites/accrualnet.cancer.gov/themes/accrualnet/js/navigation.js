/***
 * Added By: Lauren
 * Added On: September 12, 2012
 * 
 * Changes the tab color on the navigation menu. Per Ashleigh's demand :)
 ***/

(function ($) {

    $(document).ready(function() {
        $('.homepage-node-title').each(function() {
            var link = $(this).children('a');
            var color = '';
            var target = link.attr('href');
            target = target.split('/')[0];
            switch (target) {
                /* Permanently changes colors
                case '/literature':
                    link.css('color', '#105693');
                    break;
                case '/protocol_accrual_lifecycle':
                    link.css('color', '#54316E');
                    break;
                case '/communities':
                    link.css('color', '#BF5500');
                    break;
                case '/education':
                    link.css('color', '#C74532');
                    break;
                */
               
               // Determines what color would be if rolled over
                case 'literature':
                    color = '#105693';
                    break;
                case 'protocol_accrual_lifecycle':
                    color = '#54316E';
                    break;
                case 'communities':
                    color = '#BF5500';
                    break;
                case 'education':
                    color = '#C74532';
                    break;
            }
            link.css('color', color);
        });
        $('nav#main-menu').children('ul').children('li').each(function () {
            var link = $(this).children('a');
            var color = '';
            switch (link.attr('href')) {
                /* Permanently changes colors
                case '/literature':
                    link.css('color', '#105693');
                    break;
                case '/protocol_accrual_lifecycle':
                    link.css('color', '#54316E');
                    break;
                case '/communities':
                    link.css('color', '#BF5500');
                    break;
                case '/education':
                    link.css('color', '#C74532');
                    break;
                */
               
               // Determines what color would be if rolled over
                case '/literature':
                    color = '#105693';
                    break;
                case '/protocol_accrual_lifecycle':
                    color = '#54316E';
                    break;
                case '/communities':
                    color = '#BF5500';
                    break;
                case '/education':
                    color = '#C74532';
                    break;
            }
            
            // If this is not an active tab (roll-out color change effects it
            // if it is) then change the roll over color
            if (!link.hasClass('active-trail')) {
                $(this).hover(function () {
                    link.css('color', color);
                    
                }, function () {
                    link.css('color', '#888888');
                    
                });
            }
            
        });

    });
}) (jQuery);

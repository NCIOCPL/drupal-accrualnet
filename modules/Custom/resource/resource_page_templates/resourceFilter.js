/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


(function ($) {
    $(document).ready(function() {
        



        
        $('#resource-ajax-filter').insertAfter($('#block-an-navigation-left-nav'));
        
        

        $('#content').append($('#results-div'));
        
        $('ul.pager').addClass('literature-pager');
        $('li.pager-ellipsis').css('display', 'none');
        $('li.pager-last').css('display', 'none');
        $('#title-results-pager').append($('ul.pager').clone());
        
        $('.strategy-rollup').css('display', 'none');
        $('.filter-checkbox').click(function (e){
            if($(this).children('input').attr('checked')){
               $(this).children('input').attr('checked',0);
                $(this).children('span').removeClass("checked");
                $(this).children('span').addClass("unchecked");
               $(this).children('input').change();
            }
           else{
               $(this).children('input').attr('checked',1);
               $(this).children('span').removeClass("unchecked");
               $(this).children('span').addClass("checked");
               $(this).children('input').change();
           }
        });
       
        
        $('.stage-checkbox').click(function (e) {
                $(this).next().toggle();
            
        });
        
        // Reset the filter by just reloading the base page
        var $resetFilter = $('form#resource-ajax-filter').attr('action');
        $('#filter-results').append($('<div class="reset-filter"><span class="button"><a href="' + $resetFilter + '">Reset Filter</a></span></div>'));
    
    
        $('<span class="filter-arrow collapsed">► </span>').insertBefore($('#filter-lifecycle, #filter-rtype').children('legend').children('span'));
        $('#filter-lifecycle, #filter-rtype').children('legend').next().css('display', 'none');
        $($('#filter-lifecycle, #filter-rtype').children('legend')).click(function () {
            $(this).next().toggle();
            if ($(this).children('.filter-arrow').hasClass('collapsed')) {
                $(this).children('.filter-arrow').html("▼ ");
                $(this).children('.filter-arrow').removeClass('collapsed');
                $(this).children('.filter-arrow').addClass('expanded');
            } else if ($(this).children('.filter-arrow').hasClass('expanded')) {
                $(this).children('.filter-arrow').html("► ");
                $(this).children('.filter-arrow').addClass('collapsed');
                $(this).children('.filter-arrow').removeClass('expanded');
            }
        });

    });

}) (jQuery);
function refreshResources(lifecycle, rtype, page, sort, order) {
	if(!page) page = 0;
	if(!sort) sort = '';
	if(!order) order = '';
        if (!lifecycle) lifecycle = '';
        if (!rtype) rtype = '';
        
        

	jQuery.ajax({
		cache: false,
		url: Drupal.settings.basePath + '?q=' + Drupal.settings.qPath + '/pager/callback',
		data: {page: page, sort: sort, order: order, lifecycle: lifecycle, rtype: rtype},
		dataType: 'text',
		error: function(request, status, error) {
			/*alert(status); not sure why this error happens... so just reset all filters;
                         * pretty sure it just happens when trying to submit null values like removing
                         * the last selected option or hitting filter with nothign selected
                         */
                        refreshResources(null, null, 0, null, null);
		},
		success: function(data, status, request) {
			var html = data;

			jQuery('#results-div').html(html);
			
			jQuery('#results-div th a').
				add('#results-div .pager-item a')
				.add('#results-div .pager-first a')
				.add('#results-div .pager-previous a')
				.add('#results-div .pager-next a')
				.add('#results-div .pager-last a')
					.click(function(el, a, b, c) {
						var url = jQuery.url(el.currentTarget.getAttribute('href'));
						refreshResources(lifecycle, rtype, url.param('page'), url.param('sort'), url.param('order'));
					
						return (false);
					});
		}
	});
}
	
function initializeResources() {
	jQuery(document).ready(function() {
		refreshResources();
	});
}

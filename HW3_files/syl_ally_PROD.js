// Ally
window.ALLY_CFG = {
    'baseUrl': 'https://prod.ally.ac',
    'clientId': 12138,
    'lti13Id': '10020000000000666'
};
$.getScript(ALLY_CFG.baseUrl + '/integration/canvas/ally.js');

// Extra Menu Icon
    var styleAdded = false;  
    function addMenuItem(linkText, linkhref, icon) {  
        var iconHtml = '',  
            itemHtml,  
            linkId = linkText.split(' ').join('_'),  
            iconCSS = '<style type="text/css">' +  
                '   i.custom_menu_list_icon:before {' +  
                '       font-size: 27px;' +  
                '       width: 27px;' +  
                '       line-height: 27px;' +  
                '   }' +  
                '   i.custom_menu_list_icon {' +  
                '       width: 27px;' +  
                '       height: 27px;' +  
                '   }' +  
                '   body.primary-nav-expanded .menu-item__text.custom-menu-item__text {' +  
                '       white-space: normal;' +  
                '       padding: 0 2px;' +  
                '   }' +  
                '</style>';  
        if (icon !== '') {  
            // If it is a Canvas icon  
            if (icon.indexOf('icon') === 0) {  
                iconHtml = '<div class="menu-item-icon-container" role="presentation"><i class="' + icon + ' custom_menu_list_icon"></i></div>';  
            // for an svg or other image  
            } else if (icon !== '') {  
                iconHtml = '<div class="menu-item-icon-container" role="presentation">' + icon + '</div>';  
            }  
        }  
        // Build item html  
        itemHtml = '<li class="ic-app-header__menu-list-item ">' +  
                '   <a id="global_nav_' + linkId + '" href="' + linkhref + '" class="ic-app-header__menu-list-link" target=_blank>' + iconHtml +  
                '       <div class="menu-item__text custom-menu-item__text">' + linkText + '</div>' +  
                '   </a>' +  
                '</li>';  
	//$('#menu').append(itemHtml);
	$("#menu li:eq(4)").after(itemHtml); 
        // Add some custom css to the head the first time  
        if (!styleAdded) {  
            $('head').append(iconCSS);  
            styleAdded = true;  
        }  
            
    } 
$(document).ready(function() {  
 addMenuItem('Resources','https://success.oregonstate.edu/where-do-I-go', 'icon-note-light', '_blank');
});
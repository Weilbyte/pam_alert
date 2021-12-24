#include <stdio.h>
#include <string.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <curl/curl.h>
#include <curl/mprintf.h>

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);

    char *user;
    char *rhost;
    char *ruser;
    char *service;

    (void) pam_get_item(pamh, PAM_USER, &user);
    (void) pam_get_item(pamh, PAM_SERVICE, &service);
    (void) pam_get_item(pamh, PAM_RHOST, &rhost);
    (void) pam_get_item(pamh, PAM_RUSER, &ruser);
    
    if (argv[0] && strstr(service, "sshd")) {
        curl_global_init(CURL_GLOBAL_ALL);

        CURL *curlh = curl_easy_init();
        
        if (curlh) {
            curl_easy_setopt(curlh, CURLOPT_URL, argv[0]);
            curl_easy_setopt(curlh, CURLOPT_POSTFIELDS, curl_maprintf("{\"text\" : \"⚠️ SSH login to `%s@%s`, from `%s`\"}", user, hostname, rhost));
            curl_easy_perform(curlh);

            curl_easy_cleanup(curlh);
        }
        curl_global_cleanup();
    }

    return PAM_SUCCESS;
}
#include "mongoose.h"
#include "backend_C.c" 

static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    // Route 1: The Generate Button
    if (mg_strcmp(hm->uri, mg_str("/api/generate")) == 0) {
        
        initializeBackend(); // Crucial: Resets arrays for a fresh generation
        loadCourses(); 
        loadRooms();
        
        if (generateTimetable(0, 0)) {
            saveTimetable();
            mg_http_reply(c, 200, "Access-Control-Allow-Origin: *\r\nContent-Type: application/json\r\n", "{\"status\":\"success\"}");
        } else {
            mg_http_reply(c, 400, "Access-Control-Allow-Origin: *\r\nContent-Type: application/json\r\n", "{\"status\":\"fail\"}");
        }
    } 
    // Route 2: The Save Availability Button
    else if (mg_strcmp(hm->uri, mg_str("/api/save_availability")) == 0) {
        // Here is where we will eventually parse the JSON from your grid
        mg_http_reply(c, 200, "Access-Control-Allow-Origin: *\r\nContent-Type: application/json\r\n", "{\"status\":\"success\"}");
    }
    // Route 3: Serve the HTML/CSS files
    else {
        struct mg_http_serve_opts opts = {.root_dir = "."};
        mg_http_serve_dir(c, hm, &opts);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);
  
  printf("Server starting at http://localhost:8000\n");
  
  mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, NULL);
  
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  
  mg_mgr_free(&mgr);
  return 0;
}
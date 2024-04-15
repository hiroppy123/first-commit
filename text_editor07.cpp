#include <gtk/gtk.h>
#include <gtk/gtkx.h>



static void copy_text(GtkWidget *widget, gpointer data) {
  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);

  GtkTextIter start, end;
  gtk_text_buffer_get_bounds(buffer, &start, &end);

  if (!gtk_text_iter_equal(&start, &end)) {
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD); // クリップボードを取得
    gtk_clipboard_set_text(clipboard, text, -1); // テキストをクリップボードにコピー
    g_free(text);
  }
}



static void copy_text_handler(GtkWidget *widget, gpointer data) {
  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);

  GtkTextIter start, end;
  gtk_text_buffer_get_bounds(buffer, &start, &end);

  if (!gtk_text_iter_equal(&start, &end)) {
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, TRUE);
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(clipboard, text, -1);
    g_free(text);
  }
}



static void paste_text(GtkWidget *widget, gpointer data) {
  GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
  gchar *text = gtk_clipboard_wait_for_text(clipboard);

  // Check if text was retrieved from clipboard
  if (text == NULL) {
    g_warning("Failed to get text from clipboard");
    return;
  }

  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);

  // Paste text at the end of the buffer
  GtkTextIter end;
  gtk_text_buffer_get_end_iter(buffer, &end);
  gtk_text_buffer_insert(buffer, &end, text, -1);

  g_free(text);
}



static void save_text(GtkWidget *widget, gpointer data) {
  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);

  // Get text content
  GtkTextIter start, end;
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  if (text == NULL) {
    g_warning("Failed to get text from buffer");
    return;
  }

  // Open file dialog
  GtkWidget *window = gtk_widget_get_toplevel(widget);
  GtkWidget *dialog = gtk_file_chooser_dialog_new(
      "Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE,
      "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    // Open file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
      g_warning("Failed to open file for writing: %s", filename);
      g_free(filename);
      g_free(text);
      gtk_widget_destroy(dialog);
      return;
    }

    // Write text content to file
    if (fprintf(file, "%s", text) < 0) {
      g_warning("Failed to write text to file: %s", filename);
    }
    fclose(file);

    g_free(filename);
  }

  g_free(text);
  gtk_widget_destroy(dialog);
}



static void open_file(GtkWidget *widget, gpointer data) {
  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(text_view);

  // Open file dialog
  GtkWidget *window = gtk_widget_get_toplevel(widget);
  GtkWidget *dialog = gtk_file_chooser_dialog_new(
      "Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN,
      "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    // Open file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
      g_warning("Failed to open file for reading: %s", filename);
      g_free(filename);
      gtk_widget_destroy(dialog);
      return;
    }

    // Read file content
    GString *content = g_string_new(NULL);
    gchar buffer[BUFSIZ];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      g_string_append(content, buffer);
    }

    // Insert text content to buffer
    gtk_text_buffer_set_text(text_buffer, content->str, -1);

    g_string_free(content, TRUE); // Free memory allocated with GString
    fclose(file);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}



// グローバル変数でフォントサイズを管理
int font_size = 16;

// フォントサイズを変更する関数
static void change_font_size(GtkWidget *widget, gpointer data) {
  GtkTextView *text_view = GTK_TEXT_VIEW(data);
  GtkCssProvider *provider = gtk_css_provider_new();
  gchar *css = g_strdup_printf("* { font-size: %dpx; }", font_size);
  gtk_css_provider_load_from_data(provider, css, -1, NULL);
  GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(text_view));
  gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_free(css);
  g_object_unref(provider);
}

// フォントサイズを増やす関数
static void increase_font_size(GtkWidget *widget, gpointer data) {
  font_size++;
  change_font_size(widget, data);
}

// フォントサイズを減らす関数
static void decrease_font_size(GtkWidget *widget, gpointer data) {
  font_size--;
  change_font_size(widget, data);
}

// フォントサイズをデフォルトの12pxにリセットする関数
static void reset_font_size(GtkWidget *widget, gpointer data) {
  font_size = 16; // フォントサイズをデフォルトの24pxに設定
  change_font_size(widget, data); // フォントサイズを変更する関数を呼び出す
}



int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  // ウィジェットの作成
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  // ウィンドウのデフォルトの大きさを設定
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(window), box);

  GtkWidget *text_view = gtk_text_view_new();
  gtk_widget_set_size_request(text_view, -1, 600);

  GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

  GtkWidget *grid = gtk_grid_new();

  // ボタンの作成とシグナル接続
  GCallback callbacks[] = {
    G_CALLBACK(copy_text_handler),
    G_CALLBACK(paste_text),
    G_CALLBACK(save_text),
    G_CALLBACK(open_file),
    G_CALLBACK(reset_font_size),
  };
  gchar *button_labels[] = {
    g_strdup("Copy"),
    g_strdup("Paste"),
    g_strdup("Save"),
    g_strdup("Open"),
    g_strdup("Change Font Size"),
  };
  
  
  // プラスボタンとマイナスボタンの作成
  GtkWidget *plus_button = gtk_button_new_with_label("+");
  GtkWidget *minus_button = gtk_button_new_with_label("-");
  
  // シグナル接続
  g_signal_connect(plus_button, "clicked", G_CALLBACK(increase_font_size), text_view);
  g_signal_connect(minus_button, "clicked", G_CALLBACK(decrease_font_size), text_view);  
    
  
  
  GtkWidget *buttons[G_N_ELEMENTS(button_labels)];
  for (int i = 0; i < G_N_ELEMENTS(button_labels); i++) {
    buttons[i] = gtk_button_new_with_label(button_labels[i]);
    g_signal_connect(buttons[i], "clicked", callbacks[i], text_view);
  }

  
   // グリッドへの配置
  for (int i = 0; i < G_N_ELEMENTS(button_labels); i++) {
    gtk_grid_attach(GTK_GRID(grid), buttons[i], i, 0, 1, 1);
  }
  gtk_grid_attach(GTK_GRID(grid), plus_button, G_N_ELEMENTS(button_labels), 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), minus_button, G_N_ELEMENTS(button_labels) + 1, 0, 1, 1); 
  
  
  // ウィジェットの追加と表示
  gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), grid, FALSE, FALSE, 0);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}


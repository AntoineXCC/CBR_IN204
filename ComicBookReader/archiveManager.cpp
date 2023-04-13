#include "archiveManager.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <archive.h>
#include <archive_entry.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

void Zip(QFileInfoList fileList, QString zipPath) {
  std::string S = zipPath.toStdString();
  const char* outname = S.c_str();

  struct archive *a;
  struct archive_entry *entry;
  struct stat st;
  char buff[8192];
  int len;
  int fd;

  a = archive_write_new();
  archive_write_set_format_zip(a);
  archive_write_open_filename(a, outname);
  for(int i=0;i != fileList.size(); i++){
    QString filePath=fileList.at(i).filePath();
    QFile file(filePath);

    std::string filePathStr = filePath.toStdString();
    const char* filePathChar = filePathStr.c_str();
    std::string filenameStd = file.fileName().section("/",-1,-1).toStdString();
    const char* filename = filenameStd.c_str();

    stat(filePathChar, &st);
    entry = archive_entry_new();
    archive_entry_set_pathname(entry, filename);
    archive_entry_set_size(entry, st.st_size);
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(a, entry);
    fd = open(filePathChar, O_RDONLY);
    len = read(fd, buff, sizeof(buff));
    while ( len > 0 ) {
        archive_write_data(a, buff, len);
        len = read(fd, buff, sizeof(buff));
    }
    close(fd);
    archive_entry_free(entry);
  }
  archive_write_close(a);
  archive_write_free(a);
}

void Unzip(QString zipPath, QString path) {
  std::string S = zipPath.toStdString();
  const char* filename = S.c_str();

  struct archive *a;
  struct archive *ext;
  struct archive_entry *entry;
  int flags;
  int r;

  /* Select the extraction path */
  std::string pathName = path.toStdString() + '/';

  /* Select which attributes we want to restore. */
  flags = ARCHIVE_EXTRACT_TIME;
  flags |= ARCHIVE_EXTRACT_PERM;
  flags |= ARCHIVE_EXTRACT_ACL;
  flags |= ARCHIVE_EXTRACT_FFLAGS;

  a = archive_read_new();
  archive_read_support_format_all(a);
  archive_read_support_filter_all(a);
  ext = archive_write_disk_new();
  archive_write_disk_set_options(ext, flags);
  archive_write_disk_set_standard_lookup(ext);
  if ((r = archive_read_open_filename(a, filename, 10240)))
    exit(1);
  for (;;) {
    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF)
      break;
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
      exit(1);
    const char* currFile = archive_entry_pathname(entry);
    // To get only the file and not parent directory
    std::string tmp = QString(currFile).split('/').last().toStdString();
    currFile = tmp.c_str();
    const std::string fullOutputPath = pathName + currFile;
    archive_entry_set_pathname(entry, fullOutputPath.c_str());
    r = archive_write_header(ext, entry);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    else if (archive_entry_size(entry) > 0) {
      r = copy_data(a, ext);
      if (r < ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(ext));
      if (r < ARCHIVE_WARN) {
        exit(1);
      }
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    if (r < ARCHIVE_WARN)
      exit(1);
  }
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);
}

int copy_data(struct archive *ar, struct archive *aw) {
  int r;
  const void *buff;
  size_t size;
  la_int64_t offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF)
      return (ARCHIVE_OK);
    if (r < ARCHIVE_OK) {
      std::cout<<"Ici"<<std::endl;
      return (r);
    }
    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(aw));
      return (r);
    }
  }
}



/*
 * Strawberry Music Player
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DISCORDRPC_H
#define DISCORDRPC_H

#include "config.h"

#include <QObject>

#include "core/player.h"
#include "playlist/playlistmanager.h"
#include "includes/shared_ptr.h"

namespace discord {

class RichPresence : public QObject {
  Q_OBJECT

 public:
  explicit RichPresence(const SharedPtr<Player> player,
                        const SharedPtr<PlaylistManager> playlist_manager,
                        QObject *parent = nullptr);
  ~RichPresence();

  void Stop();

 private Q_SLOTS:
  void EngineStateChanged(EngineBase::State newState);
  void CurrentSongChanged(const Song &song);
  void Seeked(const qint64 microseconds);

 private:
  void CheckEnabled();
  void SendPresenceUpdate();
  void SetTimestamp(const qint64 seekMicroseconds = 0);

  const SharedPtr<Player> player_;
  const SharedPtr<PlaylistManager> playlist_manager_;

  struct {
    QString title;
    QString artist;
    QString album;
    qint64 startTimestamp;
    qint64 lengthSecs;
    qint64 seekSecs;
  } activity_;
  qint64 send_presence_timestamp_;
  bool is_enabled_;
};

}  // namespace discord

#endif  // DISCORDRPC_H

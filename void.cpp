void Player::Update()
{
    // 地面に着地したらジャンプ回数リセット
    if (IsGrounded()) {
        jumpCount = 0;
    }

    // ジャンプチャージ開始（ジャンプ回数がmaxJumpCount未満の時のみ）
    if (CheckHitKey(KEY_INPUT_SPACE) && !isJumpCharging && jumpCount < maxJumpCount) {
        isJumpCharging = true;
        jumpChargeStartTime = GetNowCount();
    }

    // ジャンプチャージ終了（キーを離した瞬間、ジャンプ回数がmaxJumpCount未満の時のみジャンプ）
    if (!CheckHitKey(KEY_INPUT_SPACE) && isJumpCharging) {
        isJumpCharging = false;
        jumpChargeEndTime = GetNowCount();

        if (jumpCount < maxJumpCount) {
            int chargeDuration = jumpChargeEndTime - jumpChargeStartTime;
            float minPower = 8.0f;
            float mPower = minPower + (maxPower - minPower) * std::min(std::max(chargeDuration, minDuration), maxDuration) / (float)(maxDuration);
axPower = 18.0f;
            int minDuration = 100;
            int maxDuration = 700;
			float jumpPower = minPower + (maxPower - minPower) * std::min(std::max(chargeDuration, minDuration), maxDuration) / (float)(maxDuration);
            // ジャンプ処理
            velocity.y = -jumpPower;
            jumpCount++; // ジャンプ回数を増やす
        }
    }

    // ...他のUpdate処理...
}
